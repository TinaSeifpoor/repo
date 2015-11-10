#include "extractlandmarks.h"
#include <opencv2/opencv.hpp>
#include <intraface/FaceAlignment.h>
#include <intraface/XXDescriptor.h>
#include <QString>
#include <cmath>
#include "procrustes.h"
#define DEBUGGER
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
            cv::Mat procrustesLandmarks = convertLandmarksForProcrustes(landmarks);
            p.procrustes(convertLandmarksForProcrustes(goldenLandmarks), procrustesLandmarks);

#ifdef DEBUGGER
            cv::FileStorage debugger("d:/log.txt",cv::FileStorage::WRITE);
#endif

#ifdef DEBUGGER
            debugger << "LandmarksFrom" << procrustesLandmarks;
            debugger << "LandmarksTo" << p.Yprime;
#endif

            cout << "From: " << endl << procrustesLandmarks << endl << "To:" << p.Yprime << endl;

            // Translate our image coordinates to mean so that we can apply rotation & scale
            // Our 0,0 should be mean of our landmark points in frame
            cv::Mat translationToZero = cv::Mat::eye(3,3,CV_32F);
            translationToZero.at<float>(0,2) = - p.mu_y(0);
            translationToZero.at<float>(1,2) = - p.mu_y(1);
            std::cout << "translation 1 matrix" << std::endl << translationToZero << std::endl;

#ifdef DEBUGGER
            debugger << "translationToZero" << translationToZero;
#endif

            // Rotation
            cv::Mat rotationPart = cv::Mat::eye(3,3,CV_32F);
            cv::Mat(p.rotation.t()).copyTo(rotationPart(cv::Range(0,2),cv::Range(0,2)));
            std::cout << "rotation matrix" << std::endl << rotationPart << std::endl;

#ifdef DEBUGGER
            debugger << "rotation" << rotationPart;
#endif
            // Scale
            cv::Mat scalePart = cv::Mat::eye(3,3,CV_32F);
            scalePart.at<float>(0,0) =  p.scale;
            scalePart.at<float>(1,1) =  p.scale;
            std::cout << "scale matrix" << std::endl << scalePart << std::endl;

#ifdef DEBUGGER
            debugger << "scalePart" << scalePart;
#endif
            // Translate our image coordinates to mean of target so that we are translated back to image domain (0,0) is top-left
            // AND we align our faces

            cv::Mat translationFromZero = cv::Mat::eye(3,3,CV_32F);
            translationFromZero.at<float>(0,2) = p.mu_x(0);
            translationFromZero.at<float>(1,2) = p.mu_x(1);
            std::cout << "translation 2 matrix" << std::endl << translationFromZero << std::endl;

#ifdef DEBUGGER
            debugger << "translationFromZero" << translationFromZero;
#endif
            // Affine
            cv::Mat affinePart = translationFromZero * scalePart * rotationPart * translationToZero;

#ifdef DEBUGGER
            debugger << "affinePart" << affinePart;
#endif

            cout << "Affine part" << endl << affinePart << endl;
            imageP = frame.clone();
            cv::warpPerspective(imageP, imageP,affinePart, imageP.size());

//            cv::warpAffine(imageP, imageP,affineTrans, imageP.size());


            showLandmarks(goldenLandmarks, imageP, cv::Scalar(255,0,0));
        }
        return imageP;
    } else {
        return cv::Mat();
    }
}
