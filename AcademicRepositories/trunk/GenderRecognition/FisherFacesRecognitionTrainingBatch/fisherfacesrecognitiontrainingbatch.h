#ifndef FISHERFACESRECOGNITIONTRAININGBATCH_H
#define FISHERFACESRECOGNITIONTRAININGBATCH_H
#include <QObject>
class FisherFaceRecognizer;
class FisherFacesRecognitionTrainingBatch : public QObject
{
    Q_OBJECT
public:
    FisherFacesRecognitionTrainingBatch();
    void showUsage() const;
public slots:
    void go();
private:
    FisherFaceRecognizer*recognizer;
};

#endif // FISHERFACESRECOGNITIONTRAININGBATCH_H
