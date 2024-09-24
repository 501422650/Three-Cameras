//
// Created by Wind on 2024/4/9.
//

#ifndef CAMERA_IMAGEPROVIDER_H
#define CAMERA_IMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QQuickItem>

class ImageProvider : public QQuickItem {
public:
    ImageProvider();

// QQuickImageProvider interface (重写一个方法，也可以重新requestPixmap(),用于qml找图片提供者请求图片的格式)
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);

public:
    QImage m_img;

};


#endif //CAMERA_IMAGEPROVIDER_H
