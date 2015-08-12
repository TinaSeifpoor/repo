#include "fisherfacerecognizer.h"
#include <QImage>
#include "common.h"
#include "opencv2/opencv.hpp"
#include <QDebug>
class FisherFaceRecognizerPrivate
{
public:
    cv::Ptr<cv::FaceRecognizer> model;
    void reshapeData(QList<QImage> images, QVector<int> labels, std::vector<cv::Mat>& imagesOut, std::vector<int>& labelsOut) {
        Q_ASSERT(images.count()==labels.count());
        labelsOut = labels.toStdVector();
        for (int i=0; i<images.count();++i) {
            imagesOut.push_back(prepareImage(images.at(i)));
        }
    }

    cv::Mat prepareImage(QImage input) {
        return toGray(Common::QImageToCvMat(normalizeImage(input)));
    }

    QImage normalizeImage(QImage input) {
        return input.scaled(64,64);
    }


    cv::Mat toGray(cv::Mat src) {
        // Create and return normalized image:
        cv::Mat dst;
        switch(src.channels()) {
        case 3:
        case 4:
            cv::cvtColor(src, dst, CV_BGR2GRAY);
            break;
        default:
            src.copyTo(dst);
            break;
        }
        return dst;
    }
};


FisherFaceRecognizer::FisherFaceRecognizer():
    d(new FisherFaceRecognizerPrivate())
{
    d->model = cv::createFisherFaceRecognizer();

//    d->model->load("lastmodel.csv");
}

FisherFaceRecognizer::~FisherFaceRecognizer()
{
    delete d;
}

void FisherFaceRecognizer::trainFaces(QList<QImage> images, QVector<int> labels)
{
    std::vector<cv::Mat> imagesForTrain;
    std::vector<int> labelsForTrain;
    d->reshapeData(images, labels, imagesForTrain, labelsForTrain);
    d->model->train(imagesForTrain, labelsForTrain);
    d->model->save("lastmodel.csv");
}

int FisherFaceRecognizer::predictFace(QImage image)
{
    double confidence;
    int label;
    cv::Mat testMat = d->prepareImage(image);
    cv::imwrite("d:/test.jpg",testMat);
    int l = d->model->predict(testMat);

    d->model->predict(testMat,label, confidence);
    qDebug() << "Predicted class: " << label << " Confidence: " << confidence;
    return label;
}
