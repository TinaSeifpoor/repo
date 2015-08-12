#include "fisherfacerecognizer.h"
#include <QImage>
#include "common.h"
#include "opencv2/opencv.hpp"
#include <QDebug>
class FisherFaceRecognizerPrivate
{
public:
    cv::Ptr<cv::FaceRecognizer> model;
    void reshapeData(QList<QImage> images, QVector<int> labels) {
        imagesForTrain.clear();
        labelsForTrain.clear();
        Q_ASSERT(images.count()==labels.count());
        labelsForTrain = labels.toStdVector();
        for (int i=0; i<images.count();++i) {
            imagesForTrain.push_back(prepareImage(images.at(i)));
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

    std::vector<cv::Mat> imagesForTrain;
    std::vector<int> labelsForTrain;

    static cv::Mat norm_0_255(cv::InputArray _src) {
        cv::Mat src = _src.getMat();
        // Create and return normalized image:
        cv::Mat dst;
        switch(src.channels()) {
        case 1:
            cv::normalize(_src, dst, 0, 255, cv::NORM_MINMAX, CV_8UC1);
            break;
        case 3:
            cv::normalize(_src, dst, 0, 255, cv::NORM_MINMAX, CV_8UC3);
            break;
        default:
            src.copyTo(dst);
            break;
        }
        return dst;
    }

    void saveFisherFaces() {
        // Here is how to get the eigenvalues of this Eigenfaces model:
        cv::Mat eigenvalues = model->getMat("eigenvalues");
        // And we can do the same to display the Eigenvectors (read Eigenfaces):
        cv::Mat W = model->getMat("eigenvectors");
        // Get the sample mean from the training data
        cv::Mat mean = model->getMat("mean");
        // Display or save:
        cv::imwrite("mean.png", norm_0_255(mean.reshape(1, imagesForTrain[0].rows)));
        // Display or save the first, at most 16 Fisherfaces:
        for (int i = 0; i < cv::min(16, W.cols); i++) {
            using namespace cv;
            using namespace std;
            string msg = format("Eigenvalue #%d = %.5f", i, eigenvalues.at<double>(i));
            cout << msg << endl;
            // get eigenvector #i
            Mat ev = W.col(i).clone();
            // Reshape to original size & normalize to [0...255] for imshow.
            Mat grayscale = norm_0_255(ev.reshape(1, imagesForTrain[0].rows));
            // Show the image & apply a Bone colormap for better sensing.
            Mat cgrayscale;
            applyColorMap(grayscale, cgrayscale, COLORMAP_BONE);
            // Display or save:
            imwrite(format("fisherface_%d.png", i), norm_0_255(cgrayscale));
        }
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

void FisherFaceRecognizer::prepareFaces(QList<QImage> images, QVector<int> labels)
{
    d->reshapeData(images, labels);
}

void FisherFaceRecognizer::trainFaces()
{

    d->model->train(d->imagesForTrain, d->labelsForTrain);
    d->model->save("lastmodel.csv");
    d->saveFisherFaces();

}

int FisherFaceRecognizer::predictFace(QImage image)
{
    double confidence;
    int label;
    cv::Mat testMat = d->prepareImage(image);
    d->model->predict(testMat,label, confidence);
    qDebug() << "Predicted class: " << label << " Confidence: " << confidence;
    return label;
}
