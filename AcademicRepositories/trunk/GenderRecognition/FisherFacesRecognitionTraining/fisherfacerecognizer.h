#ifndef FISHERFACERECOGNIZER_H
#define FISHERFACERECOGNIZER_H

#include <QList>

class QImage;
class FisherFaceRecognizerPrivate;
class FisherFaceRecognizer
{
public:
    FisherFaceRecognizer();
    ~FisherFaceRecognizer();
    void trainFaces(QList<QImage> images, QVector<int> labels);
    int predictFace(QImage image);
private:
    FisherFaceRecognizerPrivate* d;
};

#endif // FISHERFACERECOGNIZER_H
