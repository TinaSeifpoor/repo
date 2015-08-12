#include "fisherfacerecognizer.h"
#include "fisherfacesrecognitiontrainingbatch.h"
#include <QApplication>
#include <QStringList>
#include <QDir>
#include <QImageReader>
#include <QDebug>
#include <QMetaMethod>
const int FEMALEINDEX=1;
const int MALEINDEX=0;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("FaceCropper");
    QApplication::setApplicationVersion("0.1");
    QApplication::setOrganizationName("Katiksiz");

    FisherFacesRecognitionTrainingBatch batch;
    QMetaObject::invokeMethod(&batch, "go", Qt::QueuedConnection);
    return a.exec();
}


FisherFacesRecognitionTrainingBatch::FisherFacesRecognitionTrainingBatch():
    recognizer(new FisherFaceRecognizer())
{

}

class Data
{
public:
    Data(QString path) {
        addData(path);
    }

    QList<QImage> extract() const {
        QList<QImage> images;
        foreach (QFileInfo fileInfo, files) {
            images << QImage(fileInfo.filePath());
        }
        return images;
    }

    QList<QFileInfo> getFiles() const {
        return files;
    }

    int count() {
        return files.count();
    }

private:
    void addData(QString path)
    {
        QFileInfo urlInfo(path);
        if (urlInfo.exists()) {
            if (urlInfo.isDir()) {
                addDir(urlInfo);
            } else {
                addFile(urlInfo);
            }
        }
    }

    void addFile(QFileInfo fileInfo)
    {
        QImage image(fileInfo.filePath());
        if (!image.isNull()) {
            files << fileInfo;
        }
    }

    void addDir(QFileInfo dirInfo)
    {
        QDir dir(dirInfo.filePath());
        foreach (QFileInfo subDirInfo, dir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot))
            addDir(subDirInfo);
        foreach (QFileInfo fileInfo, dir.entryInfoList(QDir::Files|QDir::NoDotAndDotDot))
            addFile(fileInfo);
    }


    QList<QFileInfo> files;

};

void FisherFacesRecognitionTrainingBatch::go()
{
    QStringList arguments = qApp->arguments();
    if (arguments.count()<5) {
        showUsage();
        QMetaObject::invokeMethod(qApp, "quit", Qt::DirectConnection);
        return;
    }
    arguments.removeFirst(); // path to executable
    Data maleTrainingData(arguments.takeFirst());
    Data femaleTrainingData(arguments.takeFirst());
    {
        QList<QImage> trainingImages;
        trainingImages << maleTrainingData.extract();
        trainingImages << femaleTrainingData.extract();
        QVector<int> trainingLabels;
        trainingLabels << QVector<int>(maleTrainingData.count(), MALEINDEX) << QVector<int>(femaleTrainingData.count(), FEMALEINDEX);
        qDebug() << "Training " << trainingLabels.count() << " samples.";
        qDebug() << "Males: " << maleTrainingData.count() << "\tFemales:" << femaleTrainingData.count();
        recognizer->prepareFaces(trainingImages,trainingLabels);
    }

    recognizer->trainFaces();
    qDebug() << "Training complete!";
    int maleTrueRecognition = 0;
    int maleCount = 0;
    {
        Data maleTestData(arguments.takeFirst());
        maleCount = maleTestData.count();
        foreach (QFileInfo maleFileInfo, maleTestData.getFiles()) {
            if (recognizer->predictFace(QImage(maleFileInfo.filePath()))==MALEINDEX) ++maleTrueRecognition;
        }
    }
    int femaleTrueRecognition = 0;
    int femaleCount = 0;
    {
        Data femaleTestData(arguments.takeFirst());
        femaleCount = femaleTestData.count();
        foreach (QFileInfo femaleFileInfo, femaleTestData.getFiles()) {
            if (recognizer->predictFace(QImage(femaleFileInfo.filePath()))==FEMALEINDEX) ++femaleTrueRecognition;
        }
    }
    qDebug() << "# males: " << maleCount << "\t # recognized: " << maleTrueRecognition << "\t performance: " << (double)maleTrueRecognition / maleCount;
    qDebug() << "# females: " << femaleCount << "\t # recognized: " << femaleTrueRecognition << "\t performance: " << (double)femaleTrueRecognition / maleCount;

    QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
}


void FisherFacesRecognitionTrainingBatch::showUsage() const
{
    qDebug("Usage: FisherFacesRecognitionTrainingBatch.exe \"MaleTraining\" \"FemaleTraining\" \"MaleTest\" \"FemaleTest\"");
    qDebug("Make sure they are cropped prior to detection.");
}
