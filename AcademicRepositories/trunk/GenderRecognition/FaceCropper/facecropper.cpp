#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "facecropper.h"
#include "common.h"
#include <QSettings>
#include <QStringList>
#include <QDirIterator>
#include <QDebug>
using namespace cv;

class FaceCropperPrivate
{
public:
    FaceCropperPrivate()
    {
        QSettings settings;
        scalingFactor = settings.value("scalingFactor").toDouble();
        minimumSize = settings.value("minimumSize").toInt();
        minNeighbors = settings.value("minNeighbors").toInt();
        QDir dir(QDir::current());
        dir.cd("cascadeXML");
        QFileInfoList detectorFileInfos = dir.entryInfoList(QStringList()<<"*.xml",QDir::NoDotAndDotDot|QDir::Files);
        foreach (QFileInfo detectorFileInfo, detectorFileInfos) {
            CascadeClassifier faceDetector;
            String faceCascadeName = detectorFileInfo.absoluteFilePath().toLatin1().constData();
            if (!faceDetector.load(faceCascadeName)) {
                qFatal("Failed to load: %s", faceCascadeName);
            }
            faceDetectors << faceDetector;
        }
    }

    double scalingFactor;
    int minimumSize;
    int minNeighbors;
    QString faceDetectorXML;
    QList<CascadeClassifier> faceDetectors;
    std::vector<Rect> detect( Mat frame );
};

FaceCropper::FaceCropper() : d(new FaceCropperPrivate())
{

}

FaceCropper::~FaceCropper()
{
    delete d;
}

bool FaceCropper::crop(QImage inputImage, QList<QImage>& outputImages)
{
    Mat inputMat = Common::QImageToCvMat(inputImage, true);
    foreach(Rect rect, d->detect(inputMat)) {
        outputImages << Common::cvMatToQImage(inputMat(rect)).copy();
    }
    return true;
}

bool FaceCropper::crop(QImage inputImage, QList<QRect>& outputRects)
{
    Mat inputMat = Common::QImageToCvMat(inputImage, true);
    foreach(Rect rect, d->detect(inputMat)) {
        outputRects << QRect(rect.x, rect.y, rect.width, rect.height);
    }
    return true;
}

void FaceCropper::setMinNeighbors(int minNeighbors)
{
    d->minNeighbors = minNeighbors;
    QSettings settings;
    settings.setValue("minNeighbors", minNeighbors);
}

void FaceCropper::setMinimumSize(int minimumSize)
{
    d->minimumSize = minimumSize;
    QSettings settings;
    settings.setValue("minimumSize", minimumSize);
}

void FaceCropper::setScalingFactor(double scalingFactor)
{
    d->scalingFactor = scalingFactor;
    QSettings settings;
    settings.setValue("scalingFactor", scalingFactor);
}


std::vector<Rect> FaceCropperPrivate::detect( Mat frame )
{
    std::vector<Rect> faces;
    Mat frameGray;
    if (frame.channels()>1) {
        cvtColor( frame, frameGray, CV_BGR2GRAY );
    } else {
        frameGray = frame;
    }
    equalizeHist( frameGray, frameGray );

    //-- Detect faces
    for (int i=0; i<faceDetectors.count();++i) {
        faceDetectors[i].detectMultiScale(frameGray, faces, scalingFactor, minNeighbors, 0|CV_HAAR_SCALE_IMAGE, Size(minimumSize, minimumSize));
        if (faces.size()>0) {
            break;
        }
    }
    return faces;
}
