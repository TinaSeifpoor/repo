#include "cihanlandmark.h"
#include <opencv2/opencv.hpp>
#include <intraface/FaceAlignment.h>
#include <intraface/XXDescriptor.h>
#include <QString>
#include <cmath>
#include "cihanlbp.h"
#include "procrustes.h"
#include <QFileInfo>
#include "cihancommon.h"
#include "cihangoldenlandmark.h"
//#define DEBUGGER
#define RADIANS_TO_DEGREES(radians) ((radians) * (180.0 / PI))
const int lmMatType = CV_32FC1;
typedef float lmType;
namespace CihanLib {

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

} essentials;

class LandmarkPrivate
{
public:
    static cv::Mat affineFromProcrustes(Procrustes* p);

    void init(cv::Mat faceImage) {
        this->faceImage = faceImage;
        this->landmarks = CLandmark::extractFaceAndLandmarks(this->faceImage,this->faceRect);
    }

    cv::Mat faceImage;
    cv::Rect faceRect;
    LandmarkMat landmarks;
};

LandmarkMat CLandmark::extractFaceAndLandmarks(cv::Mat frame, cv::Rect& faceRect)
{
    vector<cv::Rect> faces;
    cv::Mat gray_frame;
    cv::cvtColor(frame, gray_frame, CV_BGR2GRAY);
    cv::equalizeHist(gray_frame, gray_frame);
    // face detection
    Essentials* e = &essentials;
    e->face_cascade->detectMultiScale(gray_frame, faces, 1.2, 2, 0, cv::Size(50, 50));
    LandmarkMat X, landmark;
    float bestScore = -1, score=0;
    for (int idxFace = 0 ;idxFace < faces.size(); ++idxFace) {
        cv::Rect faceRectCur = faces[idxFace];
        // face alignment
        if (e->fa->Detect(frame,faceRectCur,X,score) == INTRAFACE::IF_OK)
        {
            if (score >= bestScore) {
                bestScore = score;
                landmark = X;
                faceRect = faceRectCur;
            }
        }
    }
    return convertLandmarksForProcrustes(landmark);
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

cv::Mat CLandmark::alignImage(cv::Mat frame, const CGoldenLandmark goldenLandmarks)
{
    CLandmark clandmark(frame);
    return clandmark.alignTo(goldenLandmarks);
}

AffineMat CLandmark::alignLandmark(const LandmarkMat from, const LandmarkMat to, double& scale)
{
    Procrustes p;
    p.procrustes(from, to);
    scale = p.scale;
    return LandmarkPrivate::affineFromProcrustes(&p);
}

LandmarkMat CLandmark::generalizedProcrustes(std::vector<LandmarkMat> landmarks)
{
    Procrustes p;
    LandmarkMat meanShape;
    p.generalizedProcrustes(landmarks, meanShape,5000);
    meanShape = convertLandmarksForProcrustes(meanShape.t());
    return meanShape;
}

CLandmark::CLandmark():
    d(new LandmarkPrivate())
{

}

CLandmark::CLandmark(cv::Mat faceImage):
    d(new LandmarkPrivate())
{
    d->init(faceImage);

}

CLandmark::CLandmark(QFileInfo fileInfo):
    d(new LandmarkPrivate())
{
    d->init(cv::imread(fileInfo.filePath().toStdString()));
}

CLandmark::CLandmark(const char* filepath):
    d(new LandmarkPrivate())
{
    d->init(cv::imread(filepath));
}

CLandmark::CLandmark(const CLandmark& other):
    d(new LandmarkPrivate())
{
    *this = other;
}

CLandmark::~CLandmark()
{
    delete d;
}

cv::Mat CLandmark::alignTo(const CGoldenLandmark goldenLandmark, double scaleThresholdMin, double scaleThresholdMax)
{
    double scale;
    if (!isValid())
        return cv::Mat();
    AffineMat affinePart = CLandmark::alignLandmark(goldenLandmark.landmarks(), d->landmarks, scale);
    if (scale<scaleThresholdMin || (scaleThresholdMax!=-1 && scaleThresholdMax<scale)) {
        return cv::Mat();
    }
    cv::Mat imageP = d->faceImage.clone();
    cv::Mat mask   = goldenLandmark.mask();
    cv::Mat res = cv::Mat(mask.size(), d->faceImage.type(), cv::Scalar(255,255,255));

    cv::warpPerspective(imageP, imageP,affinePart, res.size());
    imageP.copyTo(res,mask);
#ifdef DEBUGGER
    showLandmarks(goldenLandmarks, imageP, cv::Scalar(255,0,0));
#endif
    return res;
}

cv::Mat CLandmark::operator ()() const
{
    return d->faceImage;
}

CLandmark& CLandmark::operator =(const CLandmark& other)
{
    d->faceImage = other.d->faceImage;
    d->faceRect = other.d->faceRect;
    d->landmarks = other.d->landmarks;
    return *this;
}

CLandmark& CLandmark::operator =(const cv::Mat& mat)
{
    d->init(mat);
    return *this;
}

LandmarkMat CLandmark::landmarks() const
{
    return d->landmarks;
}

bool CLandmark::isValid() const
{
    return d->landmarks.rows && d->landmarks.cols;
}




cv::Mat LandmarkPrivate::affineFromProcrustes(Procrustes* p) {
#ifdef DEBUGGER
    cv::FileStorage debugger("d:/log.txt",cv::FileStorage::APPEND);
#endif

#ifdef DEBUGGER
    debugger << "LandmarksFrom" << procrustesLandmarks;
    debugger << "LandmarksTo" << p->Yprime;
    cout << "From: " << endl << procrustesLandmarks << endl << "To:" << p->Yprime << endl;
#endif


    // Translate our image coordinates to mean so that we can apply rotation & scale
    // Our 0,0 should be mean of our landmark points in frame
    cv::Mat translationToZero = cv::Mat::eye(3,3,CV_32F);
    translationToZero.at<float>(0,2) = - p->mu_y(0);
    translationToZero.at<float>(1,2) = - p->mu_y(1);

#ifdef DEBUGGER
    std::cout << "translation 1 matrix" << std::endl << translationToZero << std::endl;
    debugger << "translationToZero" << translationToZero;
#endif

    // Rotation
    cv::Mat rotationPart = cv::Mat::eye(3,3,CV_32F);
    cv::Mat(p->rotation.t()).copyTo(rotationPart(cv::Range(0,2),cv::Range(0,2)));

#ifdef DEBUGGER
    std::cout << "rotation matrix" << std::endl << rotationPart << std::endl;
    debugger << "rotation" << rotationPart;
#endif
    // Scale
    cv::Mat scalePart = cv::Mat::eye(3,3,CV_32F);
    scalePart.at<float>(0,0) =  p->scale;
    scalePart.at<float>(1,1) =  p->scale;

#ifdef DEBUGGER
    std::cout << "scale matrix" << std::endl << scalePart << std::endl;
    debugger << "scalePart" << scalePart;
#endif
    // Translate our image coordinates to mean of target so that we are translated back to image domain (0,0) is top-left
    // AND we align our faces

    cv::Mat translationFromZero = cv::Mat::eye(3,3,CV_32F);
    translationFromZero.at<float>(0,2) = p->mu_x(0);
    translationFromZero.at<float>(1,2) = p->mu_x(1);

#ifdef DEBUGGER
    std::cout << "translation 2 matrix" << std::endl << translationFromZero << std::endl;
    debugger << "translationFromZero" << translationFromZero;
#endif
    // Affine
    cv::Mat affinePart = translationFromZero * scalePart * rotationPart * translationToZero;

#ifdef DEBUGGER
    debugger << "affinePart" << affinePart;
    cout << "Affine part" << endl << affinePart << endl;
#endif

    return affinePart;
}
}
