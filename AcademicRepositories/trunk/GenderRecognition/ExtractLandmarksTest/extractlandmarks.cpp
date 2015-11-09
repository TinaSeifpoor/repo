#include "extractlandmarks.h"
#include <opencv2/opencv.hpp>
#include <intraface/FaceAlignment.h>
#include <intraface/XXDescriptor.h>
#include <QString>
#include <cmath>
#include "procrustes.h"

#define RADIANS_TO_DEGREES(radians) ((radians) * (180.0 / PI))
const int lmMatType = CV_32FC1;
typedef float lmType;

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

cv::Mat ExtractLandmarks::extractFaceAndLandmarks(cv::Mat frame, cv::Mat& face)
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
                face = frame(faceRect);
            }
        }
    }
    return landmark;
}

float ExtractLandmarks::calculateHomography(cv::Mat fromPoints, cv::Mat toPoints, cv::Mat& homography)
{
    std::vector<cv::Point2f> fromPointsVector, toPointsVector;
    for (int i=0; i<fromPoints.cols;++i) {
        fromPointsVector.push_back(cv::Point2f(fromPoints.at<float>(0,i),fromPoints.at<float>(1,i)));
        toPointsVector  .push_back(cv::Point2f(toPoints  .at<float>(0,i),toPoints  .at<float>(1,i)));
    }
    homography = cv::findHomography(fromPointsVector, toPointsVector);
    std::vector<cv::Point2f> toPointsPrimeVector;
    cv::perspectiveTransform(fromPointsVector, toPointsPrimeVector, homography);
    float error=0;
    for (int i=0; i<toPointsPrimeVector.size(); ++i) {
        cv::Point2f primePoint = toPointsPrimeVector.at(i);
        cv::Point2f point = fromPointsVector.at(i);
        cv::Point2f distance = primePoint-point;
        error += distance.x*distance.x + distance.y*distance.y;
    }
    return error;
}

/**
 * A simple helper class to plot the points
 **/
void showLandmarksProcrustes(cv::Mat& points, cv::Mat& img, cv::Scalar color ) {
    using namespace cv;
    vector<Point2f> vec;
    points.copyTo( vec );

    for(vector<Point2f>::const_iterator it = vec.begin(); it!=vec.end(); ++it) {
        Point2f p = *it;
        circle( img, p, 2, color, 2 );
    }
}

void showLandmarks(const cv::Mat landmarks, cv::Mat& frame, cv::Scalar color = cv::Scalar(255,0,0)) {
    cv::Mat Xp = landmarks;
    for (int i = 0 ; i < Xp.cols ; i++) {
        cv::Point2f landmark = cv::Point((int)Xp.at<float>(0,i), (int)Xp.at<float>(1,i));
        cv::circle(frame,landmark, 1, color, -1);
    }
}

cv::Mat convertLandmarksForProcrustes(cv::Mat in) {
    using namespace cv;
    Mat out = Mat(in.cols, 1, CV_32FC2);
    for (int i=0; i<in.cols; ++i) {
        Vec2f& elem = out.at<Vec2f>(i,0);
        elem[0] = in.at<float>(0,i);
        elem[1] = in.at<float>(1,i);
    }
    return out;
}

cv::Mat ExtractLandmarks::alignImage(cv::Mat frame, cv::Mat goldenLandmarks)
{
    cv::Mat face;
    cv::Mat landmarks = ExtractLandmarks::extractFaceAndLandmarks(frame,face);
    if (landmarks.cols==goldenLandmarks.cols && landmarks.rows==goldenLandmarks.rows) {
        cv::Mat imageP;
        if (false) {
            cv::Mat homography;
            float error = ExtractLandmarks::calculateHomography(landmarks, goldenLandmarks, homography);
            cv::warpPerspective(frame, imageP, homography, imageP.size());
        } else {
            Procrustes p;
            p.procrustes(convertLandmarksForProcrustes(landmarks),convertLandmarksForProcrustes(goldenLandmarks));


            cv::Mat rotationPart = cv::Mat::eye(3,3,CV_32F);
            p.rotation.copyTo(rotationPart(cv::Range(0,2),cv::Range(0,2)));
//            std::cout << "rotation matrix" << std::endl << rotationPart << std::endl;

            cv::Mat scalePart = cv::Mat::eye(3,3,CV_32F) * p.scale;
//            std::cout << "scale matrix" << std::endl << scalePart << std::endl;

//            std::cout << "scale & rotate" << std::endl << rotationPart*scalePart << std::endl;

            cv::Mat translatePart = cv::Mat::eye(3,3,CV_32F);
            translatePart.at<float>(1,2) = p.translation.at<float>(0,0);
            translatePart.at<float>(0,2) = p.translation.at<float>(0,1);
//            std::cout << "translate matrix" << std::endl << translatePart << std::endl;

            cv::Mat affinePart = cv::Mat::eye(2,3,CV_32F);

            cv::Mat(scalePart * rotationPart * translatePart)(cv::Range(0,2),cv::Range(0,3)).copyTo(affinePart);

            imageP = frame.clone();
//            cv::warpAffine(imageP, imageP,affinePart, imageP.size());


            showLandmarksProcrustes(p.Yprime, imageP, cv::Scalar(0,255,0));

            showLandmarks(landmarks, imageP, cv::Scalar(0,0,255));

            showLandmarks(goldenLandmarks, imageP, cv::Scalar(255,0,0));
        }
        return imageP;
    } else {
        return cv::Mat();
    }
}
