#include "extractlandmarks.h"
#include <opencv2/opencv.hpp>
#include <intraface/FaceAlignment.h>
#include <intraface/XXDescriptor.h>
#include <QString>
struct Essentials{
    Essentials() {
        std::string detectionModel = INTRAFACEPATH "/models/DetectionModel-v1.5.bin";
        std::string trackingModel = INTRAFACEPATH "/models/TrackingModel-v1.10.bin";
        INTRAFACE::XXDescriptor xxd(4);

        fa = new INTRAFACE::FaceAlignment(detectionModel.data(), trackingModel.data(), &xxd);

        if (!fa->Initialized()) {
            cerr << "FaceAlignment cannot be initialized." << endl;
            abort();
        }
    }
    INTRAFACE::FaceAlignment*fa;
} d;


cv::Mat ExtractLandmarks::extractLandmarks(cv::Mat frame, bool* isSuccessful)
{
    cv::Rect frameRect = cv::Rect(0,0,frame.cols,frame.rows);
    cv::Mat landmarks;
    float score;
    bool success=false;
    if (d.fa->Detect(frame,frameRect,landmarks,score) == INTRAFACE::IF_OK)
    {
        // only draw valid faces
        success = score>=.5;
    }
    if (isSuccessful) {
        *isSuccessful=success;
    }
    return landmarks;
}

cv::Mat ExtractLandmarks::calculateHomography(cv::Mat fromPoints, cv::Mat toPoints)
{
    std::vector<cv::Point2f> fromPointsVector, toPointsVector;
    for (int i=0; i<fromPoints.cols;++i) {
        fromPointsVector.push_back(cv::Point2f(fromPoints.at<float>(0,i),fromPoints.at<float>(1,i)));
        toPointsVector  .push_back(cv::Point2f(toPoints  .at<float>(0,i),toPoints  .at<float>(1,i)));
    }
    return cv::findHomography(fromPointsVector, toPointsVector);
}

//cv::Mat ExtractLandmarks::calculateOPA(cv::Mat fromPoints, cv::Mat toPoints)
//{
//    cv::Mat normalizedFromPoints = normalizePoints(fromPoints);
//    cv::Mat normalizedToPoints   = normalizePoints(toPoints);

//    cv::Mat transposeNormalizedFromPoints;
//    cv::transpose(normalizedFromPoints,transposeNormalizedFromPoints);
//    cv::Mat U, S, Vt;
//    cv::SVDecomp(transposeNormalizedFromPoints*normalizedToPoints, S, U, Vt);
//    cv::Mat R;
//    cv::transpose((U*Vt),R);
//}

cv::Mat ExtractLandmarks::normalizePoints(cv::Mat points)
{

    cv::Mat normalizedPoints = points.clone();
    cv::Scalar meanScalar, stdScalar;

    cv::Mat pointsX = normalizedPoints.row(0);
    cv::meanStdDev(pointsX, meanScalar, stdScalar);
    cv::Mat pointsXNormalized = (pointsX-meanScalar);
    pointsXNormalized.copyTo(pointsX);

    cv::Mat pointsY = normalizedPoints.row(1);
    cv::meanStdDev(pointsY, meanScalar, stdScalar);
    cv::Mat pointsYNormalized = (pointsY-meanScalar);
    pointsYNormalized.copyTo(pointsY);

    return normalizedPoints;
}

cv::Mat ExtractLandmarks::alignLandmarks(cv::Mat from, cv::Mat to)
{
    return from;
}
