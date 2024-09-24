#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include "yolov5_seg_trt.h"

namespace fs = std::filesystem;

class ImageProcessor : public QObject {
Q_OBJECT

public:
    explicit ImageProcessor(QObject *parent = nullptr);


    void run();

    QString savePath;
    float conf = 0.25;
    float score = 0.25;
    std::queue<int> taskQueue;
    bool m_stopFlag;
signals:

    void badMessage(QString path, int unit, bool bad);

protected:

private:
    int padding_grid_h;
    int padding_grid_w;
    //实例化检测器
    yolov5segtrt *detector;

    std::vector<cv::Mat> splitImage(QString imagePath, int blockWidth, int blockHeight);

};

#endif // IMAGEPROCESSOR_H
