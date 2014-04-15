#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QLabel>
#include "common.h"
class ImageWindow : public QLabel
{
    Q_OBJECT
    
public:
    explicit ImageWindow(QWidget* parent = 0);

public slots:
    void showImage(Image im);
    void showImageNKeypoints(Image im, KeyPoints keyPoints);

signals:
    void clicked(double x, double y);

private:
    void mouseReleaseEvent(QMouseEvent *ev);

};

#endif // IMAGEWINDOW_H
