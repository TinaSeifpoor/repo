#include "tdfread.h"
#include "opencv2/opencv.hpp"
#include <QFile>
#include <QDataStream>
#include <QStringList>
#include <QDebug>
QList<double> readLine(QString lineText) {
    QStringList lineTexts = lineText.split("\t");
    QList<double> res;
    for (int i =0; i< lineTexts.count(); ++i) {
        res << lineTexts.value(i).toDouble();
    }
    return res;
}

cv::Mat TDFRead::read(QString filepath)
{
    QFile file(filepath);
    if (file.open(QFile::ReadOnly)) {
        QString fileText = file.readAll();
        QStringList lineTexts = fileText.split("\r\n", QString::SkipEmptyParts);
        int nRows = lineTexts.count();
        QString firstLine = lineTexts.first();
        QList<double> firstRow = readLine(firstLine);
        int nCols = firstRow.count();
        cv::Mat res(nRows, nCols, CV_64F);
        for (int col=0; col<nCols; ++col) {
            res.at<double>(0,col) = firstRow.value(col);
        }
        for (int row=1; row<nRows; ++row) {
            QString lineText = lineTexts.value(row);
            QList<double> rowValues = readLine(lineText);
            for (int col=0; col<nCols; ++col) {
                res.at<double>(row,col) = rowValues.value(col);
            }
        }
        return res;
    }
    return cv::Mat();
}

cv::Mat TDFRead::reshapeAndNormalizeLandmarks(cv::Mat landmarkPoints)
{
    cv::Scalar meanScalar, stdScalar;

    cv::Mat pointsX = landmarkPoints.col(0);
    cv::meanStdDev(pointsX, meanScalar, stdScalar);
    cv::Mat pointsXNormalized = (pointsX-meanScalar);
    pointsXNormalized.copyTo(pointsX);

    cv::Mat pointsY = landmarkPoints.col(1);
    cv::meanStdDev(pointsY, meanScalar, stdScalar);
    cv::Mat pointsYNormalized = (pointsY-meanScalar);
    pointsYNormalized.copyTo(pointsY);
//    std::cout << pointsXNormalized << pointsYNormalized << landmarkPoints;
    return landmarkPoints.reshape(1,1);
}
