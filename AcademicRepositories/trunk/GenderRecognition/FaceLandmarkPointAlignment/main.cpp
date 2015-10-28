#include <QApplication>
#include <QDir>
#include "tdfread.h"
#include "opencv2/opencv.hpp"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString dirPath = argv[1];
    QDir dir(dirPath);
    QFileInfoList fileInfoList = dir.entryInfoList(QStringList() << "*.txt", QDir::Files);
    int nFiles = fileInfoList.count();
    int nLandmarks = 77 * 2;
    cv::Mat landmarksMat(nFiles, nLandmarks, CV_64F);
    landmarksMat = 0;
    for (int iFile = 0; iFile<nFiles; ++iFile) {
        QFileInfo fileInfo = fileInfoList.value(iFile);
        cv::Mat fileMat = TDFRead::read(fileInfo.filePath());
        cv::Mat landmarksMatForFile = landmarksMat.rowRange(iFile,iFile+1);
        TDFRead::reshapeAndNormalizeLandmarks(fileMat).copyTo(landmarksMatForFile);
    }
    cv::PCA pca(landmarksMat,cv::Mat(), CV_PCA_DATA_AS_ROW);



    cv::write(cv::FileStorage("d:/landmarks.test",cv::FileStorage::WRITE), landmarksMat);
    cv::write(cv::FileStorage("d:/pcaeigenvectors.test",cv::FileStorage::WRITE), pca.eigenvectors);
    cv::write(cv::FileStorage("d:/pcaeigenvalues.test",cv::FileStorage::WRITE), pca.eigenvalues);
    cv::Mat postPCACoefficients = landmarksMat*pca.eigenvectors;
    cv::write(cv::FileStorage("d:/pcaCoefficients.test",cv::FileStorage::WRITE), postPCACoefficients);

    return -1;
}
