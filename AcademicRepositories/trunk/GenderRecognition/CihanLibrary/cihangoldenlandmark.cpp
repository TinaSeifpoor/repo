#include "cihangoldenlandmark.h"
#include "opencv2/opencv.hpp"
#include <QString>
using namespace CihanLib;

class CGoldenLandmarkPrivate {
public:
    LandmarkMat landmarks;
    cv::Mat maskImage;
    QString filepath;
    cv::RotatedRect rect;
    cv::Size2i maskSize;};


CGoldenLandmark::CGoldenLandmark(QString filepath):
    d(new CGoldenLandmarkPrivate())
{
    d->filepath = filepath;
}

bool CGoldenLandmark::load()
{
    cv::FileStorage storage(d->filepath.toStdString(), cv::FileStorage::READ);
    if (storage.isOpened()) {
        storage["goldenLandmark"            ]    >> d->landmarks;
        storage["mask_rotatedRectCenterX"   ]    >> d->rect.center.x;
        storage["mask_rotatedRectCenterY"   ]    >> d->rect.center.y;
        storage["mask_rotatedRectSizeWidth" ]    >> d->rect.size.width;
        storage["mask_rotatedRectSizeHeight"]    >> d->rect.size.height;
        storage["mask_width"                ]    >> d->maskSize.width;
        storage["mask_height"               ]    >> d->maskSize.height;

//        d->maskImage = cv::Mat(d->maskSize, CV_8UC1, cv::Scalar(0));
//        cv::ellipse(d->maskImage, d->rect, cv::Scalar(255),-1);
        d->maskImage = cv::Mat(d->maskSize, CV_8UC1, cv::Scalar(255));
        return true;
    }
    return false;
}
const float scaleFactor=1.f;
const int safetyPadding = 2;
const float yFactor = 1.f;  // y axes is 30% bigger
void CGoldenLandmark::truncate(LandmarkMat goldenLandmarks)
{
    d->landmarks = goldenLandmarks;
    { // recenter
        cv::Mat moveMatrix = cv::Mat(d->landmarks.size(), d->landmarks.type(), cv::mean(d->landmarks));
        d->landmarks = d->landmarks - moveMatrix;
    }

    cv::Mat absLandmarks = cv::abs(d->landmarks);
    float radius=0.f;
    for (int i=0; i<absLandmarks.rows; ++i) {
        cv::Point2f values=0;
        values = absLandmarks.at<cv::Point2f>(i,0);
        radius = cv::max(radius, values.x);
        radius = cv::max(radius, values.y);
    }
    float diameter = radius*2;
    cv::Size2i sizeOfEllipse = cv::Size2i(diameter*scaleFactor, diameter*scaleFactor * yFactor);
    d->maskSize = cv::Size2i(sizeOfEllipse.width+safetyPadding*scaleFactor, sizeOfEllipse.height+safetyPadding*scaleFactor*yFactor);


    d->maskImage = cv::Mat(d->maskSize,CV_8UC1, cv::Scalar(0));
    cv::Point2i centerOfEllipse = cv::Point2i(d->maskSize.width/2, d->maskSize.height/2);
    d->rect = cv::RotatedRect(centerOfEllipse, sizeOfEllipse, 0);

//    cv::ellipse(d->maskImage, d->rect,cv::Scalar(255),-1);
    d->maskImage = cv::Mat(d->maskSize, CV_8UC1, cv::Scalar(255));

    cv::Mat moveMatrix = cv::Mat(d->landmarks.size(), d->landmarks.type(), cv::Scalar(centerOfEllipse.x, centerOfEllipse.y));
    d->landmarks += moveMatrix;
}

LandmarkMat CGoldenLandmark::landmarks() const
{
    return d->landmarks;
}

cv::Mat CGoldenLandmark::mask() const
{
    return d->maskImage;
}

bool CGoldenLandmark::save() const
{
    cv::FileStorage storage("aligned_goldenLandmark.yaml", cv::FileStorage::WRITE);
    if (storage.isOpened()) {
        storage << "goldenLandmark"                 << d->landmarks;
        storage << "mask_rotatedRectCenterX"        << d->rect.center.x;
        storage << "mask_rotatedRectCenterY"        << d->rect.center.y;
        storage << "mask_rotatedRectSizeWidth"      << d->rect.size.width;
        storage << "mask_rotatedRectSizeHeight"     << d->rect.size.height;
        storage << "mask_width"                     << d->maskSize.width;
        storage << "mask_height"                    << d->maskSize.height;
        return true;
    }
    return false;

}

