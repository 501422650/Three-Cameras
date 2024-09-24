#include <QDir>
#include "imageprocessor.h"
#include "iostream"
#include "QCoreApplication"

ImageProcessor::ImageProcessor(QObject *parent)
        : QObject(parent), m_stopFlag(false), detector(new yolov5segtrt) {
    //检测器初始化
    QString engine_file = QCoreApplication::applicationDirPath() + "/Engine/yolov5x-seg-hybrid.engine";
    QString class_file = QCoreApplication::applicationDirPath() + "/Engine/labels.txt";
    detector->initConfig(engine_file.toStdString(), conf, score, class_file.toStdString());
}


//分割图像并返回分割后的图像块列表
//定义的图像块大小blockWidth，blockHeight
std::vector<cv::Mat> ImageProcessor::splitImage(const QString imagePath, const int blockWidth, const int blockHeight) {
    cv::Mat image = cv::imread(imagePath.toStdString());
    //定义图像块大小
    std::vector<cv::Mat> blocks;
    cv::Mat temp;
    int rows = image.rows;
    int cols = image.cols;
    int padding_height = 0, padding_width = 0;
    //不能完整分割的进行padding
    if ((rows % blockHeight) != 0 || (cols % blockWidth) != 0) {
        //判断哪侧需要padding
        if ((rows % blockHeight) != 0 && (cols % blockWidth) != 0) {//计算需要拼接的范围
            padding_width = blockWidth - cols % blockWidth;    //右侧
            padding_height = blockHeight - rows % blockHeight; //下侧
        } else if ((cols % blockWidth) != 0) {
            padding_width = blockWidth - cols % blockWidth;    //右侧
        } else {
            padding_height = blockHeight - rows % blockHeight; //下侧
        }
        padding_grid_h = std::ceil(float(rows) / float(blockHeight));
        padding_grid_w = std::ceil(float(cols) / float(blockWidth));
        //填充
        cv::copyMakeBorder(image, temp, 0, padding_height, 0, padding_width, cv::BORDER_CONSTANT,
                           cv::Scalar(0, 0, 0)); //在下侧和右侧填充，填充模式：边界常量，填充向量：（0，0，0）
    }
    //遍历图像，分割成快
    for (int y = 0; y < temp.rows; y += blockHeight) {
        for (int x = 0; x < temp.cols; x += blockWidth) {
            //提取当前块的图像
            cv::Mat block = temp(cv::Rect(x, y, blockWidth, blockHeight)).clone(); //克隆提取的块，确保数据独立性
            blocks.push_back(block);
        }
    }
    return blocks;
}

void ImageProcessor::run() {
    std::vector<cv::Mat> blocks;  //检测前
    std::vector<cv::Mat> blocks_; //检测后
    //创建后处理结果存储器
    std::vector<DetectResult> results;
    cv::Mat result = cv::Mat::zeros(6144, 2448, CV_8UC3);
    int blockHeight = 512, blockWidth = 512;
    while (!(m_stopFlag && taskQueue.empty())) {
        if (!taskQueue.empty()) {
            int taskID = taskQueue.front();
            bool badFlag = true;
            for (int i = 0; i < 3; ++i) {
                QDir qDir;
                QString s = QString(savePath + "/unit_%1/image_%2.bmp").arg(taskID).arg(i);
                while ((!m_stopFlag) && (!qDir.exists(s)));
                if (!m_stopFlag) {
                    blocks.clear();
                    blocks = splitImage(s, blockWidth, blockHeight);
                    //读取图像
                    int i_ = 0;
                    for (cv::Mat block: blocks) {
                        // 为检测清空存储
                        results.clear();
                        detector->detect(block, results);
                        if (!results.empty()) {
                            badFlag = false;
                        }
                        for (auto dr: results) {
                            /*=================================================================================================================================*/
                            //参数依次为：图像路径，图像分块id（0-19）,轮廓面积，置信度，box中心点x，y；
                            /*=================================================================================================================================*/
                            qDebug() << "imagePath:" << savePath << "    " << "block id:" << i_ << "    " << "area:"
                                     << dr.area << "    " << "conf:"
                                     << dr.conf << "    " << "center x:" << dr.box.x + dr.box.br().x / 2 << "    "
                                     << "center y:" << dr.box.y + dr.box.br().y / 2;

                            /*===========检测结果预览=============*/
                            // cv::imshow("review", block);
                            // cv::waitKey(200);
                            /*===========检测结果预览=============*/
                        }
                        blocks_.push_back(block);
                        i_++;
                    }
                    //拼接
                    cv::Mat Image = cv::Mat::zeros(cv::Size(2560, 2048), CV_8UC3);
                    for (int y = 0; y < padding_grid_h; y++) {
                        for (int x = 0; x < padding_grid_w; x++) {
                            cv::Rect roi(x * blocks_.at(0).cols, y * blocks_.at(0).rows, blocks_.at(0).cols,
                                         blocks_.at(0).rows);
                            blocks_.at(y * padding_grid_w + x).copyTo(Image(roi));
                        }
                    }
                    blocks_.clear();
                    //Unpadding
                    Image = Image(cv::Rect(0, 0, 2448, 2048));
                    Image.copyTo(result(cv::Rect(0, i * 2048, 2448, 2048)));
                }
            }
            QDir dir(QString(this->savePath + "/Result/unit_%1/").arg(taskID));
            if (!dir.exists()) {
                dir.mkpath(QString(this->savePath + "/Result/unit_%1/").arg(taskID));
            }
            QString newname = QString(this->savePath + "/Result/unit_%1.bmp").arg(taskID);
            cv::imwrite(newname.toStdString(), result);
            //对图像进行分块
            badMessage(QString(this->savePath + "/Result/unit_%1.bmp").arg(taskID), taskID, badFlag);
            taskQueue.pop();
            //记录已处理的图像

        }
    }
}
