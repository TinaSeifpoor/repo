#include "extractlandmarks.h"
#include <opencv2/opencv.hpp>
#include <intraface/FaceAlignment.h>
#include <intraface/XXDescriptor.h>
#include <QString>
struct Essentials{
    Essentials() {
        QString detectionModel = INTRAFACEPATH "/models/DetectionModel-v1.5.bin";
        QString trackingModel = INTRAFACEPATH "/models/TrackingModel-v1.10.bin";
        xxd = new INTRAFACE::XXDescriptor(4);

        fa = new INTRAFACE::FaceAlignment(detectionModel.toLatin1().constData(), trackingModel.toLatin1().constData(), xxd);

        if (!fa->Initialized()) {
            cerr << "FaceAlignment cannot be initialized." << endl;
            abort();
        }

        QString faceDetectionModel( INTRAFACEPATH "/models/haarcascade_frontalface_alt2.xml");
        face_cascade = new cv::CascadeClassifier;
        if( !face_cascade->load( faceDetectionModel.toStdString() ) )
        {
            qWarning("Error loading face detection model.");
            abort();
        }


    }
    INTRAFACE::FaceAlignment* operator -> (){return fa;}
    INTRAFACE::FaceAlignment*fa;
    cv::CascadeClassifier* face_cascade;
    INTRAFACE::XXDescriptor *xxd;

} d;


cv::Mat ExtractLandmarks::extractLandmarks(cv::Mat frame, bool* isSuccessful)
{
    cv::Rect frameRect = cv::Rect(0,0,frame.cols,frame.rows);
    return ExtractLandmarks::extractLandmarks(frame,frameRect,isSuccessful);
}

cv::Mat ExtractLandmarks::extractLandmarks(cv::Mat frame, cv::Rect frameRect, bool* isSuccessful)
{
    cv::Mat landmarks;
    float score;
    bool success=false;
    if (d->Detect(frame,frameRect,landmarks,score) == INTRAFACE::IF_OK)
    {
        // only draw valid faces
        success = score>=.5;
    }
    if (isSuccessful) {
        *isSuccessful=success;
    }
    return landmarks;
}

cv::Mat ExtractLandmarks::extractFaceAndLandmarks(cv::Mat frame)
{
    vector<cv::Rect> faces;
    cv::Mat gray_frame;
    cv::cvtColor(frame, gray_frame, CV_BGR2GRAY);
    cv::equalizeHist(gray_frame, gray_frame);
    // face detection
    Essentials* e = &d;
    e->face_cascade->detectMultiScale(gray_frame, faces, 1.2, 2, 0, cv::Size(50, 50));
    cv::Mat X, landmark;
    float bestScore = -1, score=0;
    for (int idxFace = 0 ;idxFace < faces.size(); ++idxFace) {
        cv::Rect faceRect = faces[idxFace];
        // face alignment
        if (e->fa->Detect(frame,faceRect,X,score) == INTRAFACE::IF_OK)
        {
            if (score >= bestScore) {
                bestScore = score;
                landmark = X;
            }
        }
    }
    return landmark;
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
