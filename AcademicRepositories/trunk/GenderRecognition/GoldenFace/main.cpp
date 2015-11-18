#include <QApplication>
#include <QLabel>
#include "opencv2/opencv.hpp"
#include "asmopencv.h"
#include "cihanlib.h"
//#define BREAKEARLY
using namespace CihanLib;
void extractGoldenLandmarks(int argc, char* argv[]);
void alignGoldenLandmarks();

int main(int argc, char *argv[])
{
//    alignGoldenLandmarks();
    CGoldenLandmark golden("aligned_goldenLandmark.yaml");
    golden.load();
    CLandmark landmark("D:/Downloads/10k Adult Faces/10kfaces/10k US Adult Faces Database/female/Aaron_Boothe_5_oval.jpg");
    cv::imwrite("d:/test.jpg",landmark.alignTo(golden));
    return 1;
}

void extractGoldenLandmarks(int argc, char *argv[])
{
        QStringList folders;
        for (int i=1; i<argc; ++i) {
            folders << argv[i];
        }
    std::vector<LandmarkMat> landmarks;
#ifdef BREAKEARLY
    int breakIt=0;
#endif
    for (int i=1; i<folders.count(); ++i) {
#ifdef BREAKEARLY
        if (++breakIt>10)
            break;
#endif
        CData data(folders[i]);
        while(data.hasNext()) {
#ifdef BREAKEARLY
            if (++breakIt>10)
                break;
#endif
            QFileInfo fileInfo;
            data >> fileInfo;
            CLandmark landmark(fileInfo);
            if (landmark.landmarks().rows && landmark.landmarks().cols) {
                landmarks.push_back(landmark.landmarks());
            }
        }
    }
    LandmarkMat goldenLandmark = CLandmark::generalizedProcrustes(landmarks);
    cv::FileStorage storage ("goldenLandmark.yaml", cv::FileStorage::WRITE);
    storage << "goldenLandmark" << goldenLandmark;
}

void alignGoldenLandmarks()
{
    LandmarkMat goldenLandmark;
    {
        cv::FileStorage storage("goldenLandmark.yaml", cv::FileStorage::READ);
        storage["goldenLandmark"] >> goldenLandmark;
    }

    CGoldenLandmark golden("aligned_goldenLandmark.yaml");
    golden.truncate(goldenLandmark);
    cv::Mat goldenOut = golden.mask().clone();
    CihanLib::CCommon::showLandmarks(golden.landmarks(), goldenOut, cv::Scalar(127));
    golden.save();
    cv::imwrite("d:/golden.jpg", goldenOut);
}
