//
// Created by Wind on 2024/4/9.
//

#include "ImageProvider.h"

#include <utility>

ImageProvider::ImageProvider() {
}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {
    return this->m_img;
}



