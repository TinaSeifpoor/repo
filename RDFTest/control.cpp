#include "control.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include <QDir>
Control::Control(): imageContainer(new ImageContainer())
{

}

void Control::setImage(QString fileString)
{
    using namespace cv;
    QFileInfo fileInfo(fileString);
    if (fileInfo.exists()) {
        cv::Mat im = cv::imread(fileInfo.filePath().toStdString());
        if (!im.empty()) {

            KeyPoints keyPoints;
    //        SiftFeatureDetector(im, im, keyPoints);
            uint nChannels = im.channels();
            Image imageGray;
            uint nCols = im.cols,
                 nRows = im.rows;
            Image imMask = Image(nRows, nCols, CV_8UC1, Scalar(255));

            if (nChannels == 3)
                cvtColor(im, imageGray, CV_BGR2GRAY);
            else
                im.copyTo(imageGray);

            SIFT fd(0, 5, 0.1, 10, 1.6);
            fd.detect(imageGray, keyPoints, imMask);


            qDebug(QString::number(keyPoints.size()).toLatin1().constData());
            this->imageContainer->setImageAndKeypoint(imageGray, keyPoints);
            emit showImageNKeypoints(imageGray, keyPoints);
        }
        else {
            qWarning(QString("File can't be read: %1").arg(fileInfo.absoluteFilePath()).toLatin1().constData());
        }
    }
    else {
        qWarning(QString("File does not exist: %1").arg(fileInfo.absoluteFilePath()).toLatin1().constData());
    }
}
