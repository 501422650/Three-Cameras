//
// Created by Wind on 2024/4/29.
//
#ifndef CAMERA_IMAGEWINDOW_H
#define CAMERA_IMAGEWINDOW_H

#include <QQuickItem>
#include <QSGNode>
#include <QSGSimpleRectNode>
#include <QSGSimpleTextureNode>
#include <QQuickWindow>
#include <QImage>
#include <QObject>

class ImageWindow : public QQuickItem {

Q_OBJECT

    QML_ELEMENT
public:
    explicit ImageWindow(QQuickItem *parent = nullptr);

public slots:

    void updateImage(const QImage &);

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

public:

private:
    QImage m_imageThumb;
};


#endif //CAMERA_IMAGEWINDOW_H
