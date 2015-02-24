#ifndef MYBASELINE_H
#define MYBASELINE_H
#include <cv.hpp>
#include <QFileInfo>
#include <QVector>
typedef cv::Mat Image;
class MyBaseLine
{
public:
    MyBaseLine();
    QVector<cv::Rect> getFace(QFileInfo imInfo);
    QVector<cv::Rect> getFace(Image im);
};

#endif // MYBASELINE_H
