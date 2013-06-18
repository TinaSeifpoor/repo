#include "MyBaseLine.h"
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
MyBaseLine::MyBaseLine()
{
}

QVector<Rect> MyBaseLine::getFace(QFileInfo imInfo)
{
    if (!imInfo.exists())
    {
        qWarning(QString("Image file \"%1\" could not be found.").arg(imInfo.filePath()).toAscii().constData());
        return QVector<Rect>();
    }

    Image im = imread(imInfo.filePath().toAscii().constData());
    return this->getFace(im);
}

QVector<Rect> MyBaseLine::getFace(Image im)
{
    std::vector<Rect> faces;
    Image imGray;
    cvtColor(im, imGray, CV_BGR2GRAY);

    CascadeClassifier face_cascade;
    QString face_cascade_name = "../haarcascade_frontalface_alt.xml";
    if (!face_cascade.load(face_cascade_name.toStdString()))
        qWarning(QString("File not loaded: %1").arg(face_cascade_name).toAscii().constData());

    face_cascade.detectMultiScale(imGray, faces);
    QVector<Rect> facesVec;
    foreach (Rect face, faces)
        facesVec << face;
    return facesVec;
}
