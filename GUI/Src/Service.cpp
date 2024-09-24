//
// Created by Wind on 2024/4/9.
//

#include <QtConcurrent>
#include "Service.h"

Service::Service() : ExposureTime(20000) {
    NeoAPI::CamInfoList &infolist = NeoAPI::CamInfoList::Get();
    win1 = nullptr;
    helloData.resize(6);
    helloData[0] = 0xEF;
    helloData[1] = 0xFE;
    helloData[2] = 0xEE;
    helloData[3] = 0xFF;
    helloData[4] = 0xFF;
    helloData[5] = 0xEF;
    HeadData.resize(4);
    HeadData[0] = 0xEF;
    HeadData[1] = 0xFE;
    HeadData[2] = 0xEE;
    HeadData[3] = 0xFF;
    imageProcessor = new ImageProcessor(this);
    int i = 0;
    for (auto &info: infolist) {
        if (info.IsConnectable()) {
            winList.insert(i, win1);
            auto camera = std::make_unique<Camera>(i, info.GetId());
            i++;
            QObject::connect(camera.get(), &Camera::SendImage, this, &Service::SendImage);
            QObject::connect(camera.get(), &Camera::addDetectorTask, this, &Service::addDetectorTask);
            cameraList.emplace_back(std::move(camera));
        }
    }
    serialPort = new QSerialPort(this);
    QObject::connect(serialPort, &QSerialPort::readyRead, this, &Service::Read_Data);
    QObject::connect(imageProcessor, &ImageProcessor::badMessage, this, &Service::badMessage);
    detectorWatcher = QtConcurrent::run([=]() {
        this->imageProcessor->m_stopFlag = false;
        this->imageProcessor->run();
    });
}

void Service::startThread(const QVariantList &list) {
    for (int i = 0;; ++i) {
        if (winList.contains(i)) {
            winList[i] = list[i].value<ImageWindow *>();
        } else {
            break;
        }
    }
    connect();
    for (auto &item: cameraList) {
        item->startStream();
    }
}

void Service::closeThread() {
    if (isConnect) {
        QString s = this->serialPort->portName();
    }
    for (auto &item: cameraList) {
        item->stopStream();
    }
    if (isConnect && serialPort->isOpen()) {
        QByteArray sendData;
        uint8_t data[2];
        sendData.append(HeadData);
        sendData.append(0xFF);
        sendData.append(0xFE);
        this->serialPort->write(sendData);

        this->serialPort->waitForBytesWritten(500);
    }
    imageProcessor->m_stopFlag = true;
    detectorWatcher.waitForFinished();
}

void Service::SendImage(int id, QImage img) {
    if (winList.contains(id) && winList[id] != nullptr) {
        winList[id]->updateImage(img);
    }
}

void Service::setWin() {
    for (auto &item: cameraList) {

    }
    addDetectorTask(0, 1);
}

bool Service::ToggleTriggerMode() {
    if (isConnect) {
        QByteArray sendData;
        uint8_t data[2];
        sendData.append(HeadData);
        sendData.append(0x02);
        data[0] = 0x0D;

        if (isTrigger) {
            data[1] = 0x01;
            isTrigger = false;
        } else {
            data[1] = 0x02;
            isTrigger = true;//采集模式
        }
        for (auto &item: cameraList) {
            QObject::disconnect(item.get(), &Camera::SendImage, this, &Service::SendImage);
        }
        Delay_MSec(200);

        for (auto &item: cameraList) {
            item->ToggleTriggerMode();
        }

        for (auto &item: cameraList) {
            QObject::connect(item.get(), &Camera::SendImage, this, &Service::SendImage);
        }
        QByteArray crc = Get_Crc16(data, sizeof(data));
        sendData.append((const char *) data, 2);
        sendData.append(crc);
        this->serialPort->write(sendData);

        this->serialPort->waitForBytesWritten(500);
        return true;
    } else {
        return false;
    }
}

void Service::SoftOrHardTrigger() {
    for (auto &item: cameraList) {
        item->SoftOrHardTrigger();
    }
}

void Service::connect() {
    for (auto &info: QSerialPortInfo::availablePorts()) {
        if (this->serialPort->isOpen()) {
            this->serialPort->close();
        }
        this->serialPort->setPortName(info.portName()); // 设置串口名字，根据实际情况修改
        this->serialPort->setBaudRate(QSerialPort::Baud115200); // 设置波特率
        this->serialPort->setDataBits(QSerialPort::Data8); // 设置数据位
        this->serialPort->setParity(QSerialPort::NoParity); // 设置校验位
        this->serialPort->setStopBits(QSerialPort::OneStop); // 设置停止位
        this->serialPort->setFlowControl(QSerialPort::NoFlowControl); // 设置流控制
        this->serialPort->open(QSerialPort::ReadWrite);
        this->serialPort->write(helloData, helloData.size());
        this->serialPort->waitForBytesWritten(500);
        Delay_MSec(1000);
        if (this->isConnect) {
            break;
        } else {
            this->serialPort->close();
        }
    }
}

void Service::Delay_MSec(unsigned int msec) {

    QEventLoop loop;//定义一个新的事件循环

    QTimer::singleShot(msec, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数

    loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出

}

void Service::Read_Data() {
    QByteArray buf;
    Delay_MSec(200);
    buf = this->serialPort->readAll();

    if (!buf.isEmpty()) {
        uint8_t a = buf[0];
        uint8_t b = buf[1];
        if (a == 0xFF && b == 0xFE) {
            isConnect = true;
        }
    }
    buf.clear();
}

void Service::changeLight(float num) {
    num /= 10;
    num *= 0.9;
    if (this->light != (int) num) {
        this->light = (int) num;
        qDebug() << light;
        if (isConnect && serialPort->isOpen()) {
            QByteArray sendData;
            uint8_t data[4];
            sendData.append(HeadData);
            sendData.append(0x04);
            data[0] = 0x0B;
            data[1] = 0x03;
            data[2] = 0x00;
            data[3] = (char) this->light;
            QByteArray crc = Get_Crc16(data, sizeof(data));
            sendData.append((const char *) data, 4);
            sendData.append(crc);
            this->serialPort->write(sendData);

            this->serialPort->waitForBytesWritten(500);
        }
    }
}

QByteArray Service::Get_Crc16(uint8_t *puchMsg, uint16_t usDataLen) {
    uint8_t uchCRCHi = 0xFF;    //高CRC 字节初始化
    uint8_t uchCRCLo = 0xFF;    //低CRC 字节初始化
    uint32_t uIndex;    //CRC 循环中的索引
    while (usDataLen--)    //传输消息缓冲区
    {
        uIndex = uchCRCHi ^ *puchMsg++; //计算CRC
        uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
        uchCRCLo = auchCRCLo[uIndex];
    }
    QByteArray crc;
    crc.append(uchCRCHi);
    crc.append(uchCRCLo);

    return crc;

}

void Service::Len_Control(int id, int mot, int dir) {
    if (isConnect) {
        QByteArray sendData;
        uint8_t data[4];
        sendData.append(HeadData);
        sendData.append(0x04);
        data[0] = 0x0A;
        data[1] = id;
        data[2] = mot;
        data[3] = dir;
        QByteArray crc = Get_Crc16(data, sizeof(data));
        sendData.append((const char *) data, 4);
        sendData.append(crc);
        this->serialPort->write(sendData);
        this->serialPort->waitForBytesWritten(500);
    }
}

void Service::SetExposureTime(int us) {
    if (us != this->ExposureTime) {
        this->ExposureTime = us;
        for (auto &item: cameraList) {
            QObject::disconnect(item.get(), &Camera::SendImage, this, &Service::SendImage);
        }
        Delay_MSec(500);
        for (auto &item: cameraList) {
            item->SetExposureTime(us);
        }
        for (auto &item: cameraList) {
            QObject::connect(item.get(), &Camera::SendImage, this, &Service::SendImage);
        }
    }
}

void Service::SetDistance(int mm) {
    double p = mm * 3.6;
    mm = (int) p;
    if (isConnect && serialPort->isOpen()) {
        QByteArray sendData;
        uint8_t data[4];
        sendData.append(HeadData);
        sendData.append(0x04);
        data[0] = 0x0B;
        data[1] = 0x02;
        data[2] = mm >> 8;
        data[3] = mm;
        QByteArray crc = Get_Crc16(data, sizeof(data));
        sendData.append((const char *) data, 4);
        sendData.append(crc);
        this->serialPort->write(sendData);
        this->serialPort->waitForBytesWritten(500);
    }
}

void Service::SetSavePath(const QString &path) {
    for (auto &item: cameraList) {
        item->savePath = path + "/";
    }
    imageProcessor->savePath = path;
}

void Service::addDetectorTask(int unit, int id) {
    saveVec[unit]++;
    if (saveVec[unit] == 3) {
        imageProcessor->taskQueue.emplace(unit);
        saveVec.remove(unit);
    }
}

void Service::badMessage(QString path, int unit, bool bad) {
    this->addList(path, unit, bad);
}

