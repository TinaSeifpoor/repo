#include <QCoreApplication>
#include "cihanlib.h"
#include "opencv2/opencv.hpp"
using CihanLib::CData;
using CihanLib::CLandmark;
using CihanLib::CLBP;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cv::FileStorage storage(argv[1], cv::FileStorage::READ);
    CihanLib::LandmarkMat goldenLandmarkMat;
    cv::read(storage["Golden"],goldenLandmarkMat);
    int goldenImageWidth, goldenImageHeight;
    storage["ImageWidth"] >> goldenImageWidth;
    storage["ImageHeight"] >> goldenImageHeight;
    cv::Mat goldenMask = cv::imread(argv[2])>128;
    for (int i=3; i<argc; ++i) {
        CData data(argv[i]);
        cv::FileStorage landmarkStorage(std::string(argv[i]) + ".yaml", cv::FileStorage::WRITE);
        cv::Mat landmark;
        while(data.hasNext()) {
            QFileInfo fileInfo;
            data >> fileInfo;
            landmark = cv::imread(fileInfo.filePath().toStdString());
            cv::Mat alignedImage = CLandmark::alignImage(landmark,goldenLandmarkMat);
            if (alignedImage.rows && alignedImage.cols) {
                cv::Mat lbpImage = CLandmark::lbpImage(alignedImage, goldenMask);
                cv::Mat lbpThreshold =
                landmarkStorage << "lbpImage" << lbpImage;
            }
            //            cv::Mat lbpImageToShow;
            //            cv::normalize(lbpImage, lbpImageToShow, 0, 255, cv::NORM_MINMAX, CV_8UC1);
            //            cv::namedWindow("");
            //            cv::imshow("",lbpImageToShow);
            //            cv::waitKey();
        }
    }
    return 1;
}
