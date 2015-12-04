#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QGraphicsScene>
#include "csimage.h"
class ImageWidgetPrivate;
class ImageWidget : public QGraphicsScene
{
    Q_OBJECT
    ImageWidgetPrivate*d;
public:
    explicit ImageWidget(QObject *parent = 0);
    ~ImageWidget();

public slots:
    void setImage(CSImage im);
};

#endif // IMAGEWIDGET_H
