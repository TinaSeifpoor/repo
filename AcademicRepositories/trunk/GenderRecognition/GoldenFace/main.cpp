#include <QApplication>
#include <QLabel>
#include "opencv2/opencv.hpp"
#include "asmopencv.h"
#include "cihanlib.h"
using namespace CihanLib;
int main(int argc, char *argv[])
{
    std::vector<LandmarkMat> landmarks;
    for (int i=1; i<argc; ++i) {
        CData data(argv[i]);
        while(data.hasNext()) {
            QFileInfo fileInfo;
            data >> fileInfo;
            CLandmark landmark(fileInfo);
            if (landmark.landmarks().rows && landmark.landmarks().cols) {
                landmarks.push_back(landmark.landmarks());
            }
        }
    }
    LandmarkMat goldenLandmark = CLandmark::generalizedProcrustes(landmarks);
    cv::FileStorage storage ("goldenlandmark.yaml", cv::FileStorage::WRITE);
    storage << "goldenlandmark" << goldenLandmark;
//    QApplication a(argc, argv);
//    cv::Mat goldenMask = ASM::QImageToCvMat(QImage(":/golden/image/goldenmask.jpg"));
//    cv::cvtColor(goldenMask, goldenMask, CV_BGRA2GRAY);
//    cv::threshold(goldenMask, goldenMask, 128, 255, cv::THRESH_BINARY);
//    qDebug() << goldenMask.type();
//    cv::FileStorage storage("storeit.yaml", cv::FileStorage::WRITE);
//    storage << "mask" << goldenMask;
//    cv::imwrite("goldenMask.png",goldenMask);
    return 1;
}
