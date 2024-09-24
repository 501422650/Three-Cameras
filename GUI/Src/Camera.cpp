//
// Created by Wind on 2024/4/16.
//

#include "Camera.h"
#include <QtConcurrent>

using namespace NeoAPI;

Camera::Camera() {
    this->Connect();
    if (this->IsConnected()) {
        this->f().TriggerMode = NeoAPI::TriggerMode::Off;
    }
}

Camera::Camera(int _id, const NeoAPI::NeoString &name) : id(_id) {
    this->Connect(name);
    this->savePath = "C:/Image/";

    if (this->IsConnected()) {
        this->f().TriggerMode = NeoAPI::TriggerMode::Off;
        NeoAPI::Image image;
        image = this->GetImage();
        m_img = QImage((const uchar *) image.GetImageData(), 2448, 2048, QImage::Format_Grayscale8);
    }
}


void Camera::startStream() {
    threadWatcher = QtConcurrent::run([=]() {
        stopFlag = false;
        this->f().ExposureTime = 20000;
        this->run();
    });
}

void Camera::run() {
    NeoAPI::Image image;
    while (!stopFlag) {
        image = this->GetImage();
        m_img = QImage((const uchar *) image.GetImageData(), 2448, 2048, QImage::Format_Grayscale8);
        if (!m_img.isNull()) {
            SendImage(this->id, m_img);
            if (this->saveFlag) {
                QDir qDir(savePath + "unit_" + QString::number(saveCount) + "/");
                if (!qDir.exists()) {
                    qDir.mkpath(savePath + "unit_" + QString::number(saveCount) + "/");
                }
                NeoString s = NeoString(
                        QString(savePath + "unit_%1/image_%2.bmp").arg(saveCount).arg(id).toLocal8Bit());
                image.Save(s);
                addDetectorTask(saveCount, id);
                saveCount++;
            }
        }
    }
}

void Camera::stopStream() {
    stopFlag = true;
    this->StopStreaming();
    this->Disconnect();
}

void Camera::ToggleTriggerMode() {
    if (this->IsConnected()) {
        if (this->f().TriggerMode == NeoAPI::TriggerMode::Off) {
            this->f().TriggerMode = NeoAPI::TriggerMode::On;
//            this->f().TriggerSource.Set(TriggerSource::Software);
            this->f().TriggerActivation.Set(TriggerActivation::RisingEdge);
            this->f().TriggerSelector.Set(TriggerSelector::FrameStart);
            this->f().TriggerSource.Set(TriggerSource::Line0);
            saveCount = 0;
            startSave();
        } else {
            stopSave();
            this->f().TriggerMode = NeoAPI::TriggerMode::Off;
        }
    }
}

void Camera::SoftOrHardTrigger() {
    if (this->IsConnected()) {
        if (this->f().TriggerMode == NeoAPI::TriggerMode::On) {
            auto e = this->f().TriggerSoftware;
            e.Execute();
        }
    }
}

void Camera::saveThread() {
    while (saveFlag || (!saveQueue.empty())) {
        try {
            if (!saveQueue.empty()) {
                NeoString s = NeoString(
                        (savePath + "Camera_" + QString::number(id) + "/image_" + QString::number(saveCount) +
                         ".bmp").toLocal8Bit());
                saveQueue.front().Save(s);
                saveQueue.pop();
                saveCount++;
            }
        } catch (FileAccessException &e) {
            qDebug() << e.GetDescription();
        }
    }
}

void Camera::startSave() {
    if (threadWatcher.isRunning()) {
        this->saveFlag = true;
    }
}

void Camera::stopSave() {
    this->saveFlag = false;
}

void Camera::SetExposureTime(int us) {
    if (this->IsConnected()) {
        this->f().ExposureTime = us;
    }
}


