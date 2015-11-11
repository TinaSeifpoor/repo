#include <QApplication>
#include <QLabel>
#include "opencv2/opencv.hpp"
#include "asmopencv.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cv::Mat goldenMask = ASM::QImageToCvMat(QImage(":/golden/image/goldenmask.jpg"));
    cv::cvtColor(goldenMask, goldenMask, CV_BGRA2GRAY);
    cv::threshold(goldenMask, goldenMask, 128, 255, cv::THRESH_BINARY);
    qDebug() << goldenMask.type();
    cv::FileStorage storage("storeit.yaml", cv::FileStorage::WRITE);
    storage << "mask" << goldenMask;
    cv::imwrite("goldenMask.png",goldenMask);
    return 1;
}
