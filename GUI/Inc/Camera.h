//
// Created by Wind on 2024/4/16.
//

#ifndef CAMERA_CAMERA_H
#define CAMERA_CAMERA_H

#include <QQuickImageProvider>
#include <QMutex>
#include <queue>
#include <QFuture>
#include "neoapi/neoapi.hpp"


class Camera : public QObject, NeoAPI::Cam {
Q_OBJECT

public:
    Camera();

    Camera(const Camera &) = delete;

    explicit Camera(int id, const NeoAPI::NeoString &name);

    void startStream();

    void stopStream();

    void ToggleTriggerMode();

    void SoftOrHardTrigger();

    void startSave();

    void stopSave();

    void SetExposureTime(int us);

    int id;
    QString savePath;

    QMutex mutex;
public:
signals:

    void SendImage(int id, QImage img);

    void addDetectorTask(int unit, int id);

private:
    QImage m_img;
    bool stopFlag = false;

    bool tFlag = false;
    QFuture<void> threadWatcher;
    int saveCount;
    bool saveFlag = false;
    std::queue<NeoAPI::Image> saveQueue;

    void run();


    void saveThread();
};


#endif //CAMERA_CAMERA_H
