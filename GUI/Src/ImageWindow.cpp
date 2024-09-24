//
// Created by Wind on 2024/4/29.
//

#include "ImageWindow.h"

ImageWindow::ImageWindow(QQuickItem *parent) : QQuickItem(parent) {
    setFlag(ItemHasContents, true);
}

void ImageWindow::updateImage(const QImage &image) {
    m_imageThumb = image;
    update();
}

QSGNode *ImageWindow::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *) {
    auto node = dynamic_cast<QSGSimpleTextureNode *>(oldNode);

    if (!node) {
        node = new QSGSimpleTextureNode();
    }
    QSGTexture *m_texture = window()->createTextureFromImage(m_imageThumb, QQuickWindow::TextureIsOpaque);
    node->setOwnsTexture(true);
    node->setRect(QRectF(QPointF(0, 0), QPointF(this->width(), this->height())));
    node->markDirty(QSGNode::DirtyForceUpdate);
    node->setTexture(m_texture);

    return node;
}
