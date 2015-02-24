#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <opencv2/opencv.hpp>
#include <QLabel>

class ImageWindow : public QLabel
{
    Q_OBJECT
    
public:
    explicit ImageWindow(QWidget* parent = 0);

public Q_SLOTS:
    void showImage(cv::Mat im);

Q_SIGNALS:
    void clicked(double x, double y);

private:
    void mouseReleaseEvent(QMouseEvent *ev);
};

#endif // IMAGEWINDOW_H
