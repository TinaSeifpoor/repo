#include <QCoreApplication>
#include "extractlandmarks.h"
#include "splitdata.h"
#include "opencv2/opencv.hpp"
#include <QDir>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString fromPath = argv[1];
    cv::FileStorage storage(argv[2], cv::FileStorage::WRITE);
//    QDir toDir(argv[2]);
//    toDir.mkpath(toDir.path());
    SplitData fromData(fromPath);
    foreach (QFileInfo fileInfo, fromData()) {
//        QString destination = toDir.filePath(fileInfo.fileName());
        cv::Mat image = cv::imread(fileInfo.filePath().toStdString());
        cv::Mat landmarks = ExtractLandmarks::extractFaceAndLandmarks(image);
//        cv::Mat destinationImage = image.clone();
//        for (int i = 0 ; i < landmarks.cols ; i++)
//            cv::circle(destinationImage,cv::Point((int)landmarks.at<float>(0,i), (int)landmarks.at<float>(1,i)), 1, cv::Scalar(0,255,0), -1);
//        cv::imwrite(destination.toStdString(),destinationImage);
        cv::write(storage,fileInfo.baseName().toStdString(),landmarks);
    }
    return 1;
}
