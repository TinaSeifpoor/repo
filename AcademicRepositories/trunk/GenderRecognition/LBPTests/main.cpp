#include <opencv2/opencv.hpp>
#include "cihanlib.h"
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
using namespace cv;
using CihanLib::CData;
using CihanLib::CLBP;
using CihanLib::CCommon;

const char* femaleDir   = "female_aligned";
const char* maleDir     = "male_aligned";
const char* femaleKey = "female";
const char* maleKey   = "male";
void featureExtractGenderData(QString dirPath, QString genderKey);
int main(int argc, const char *argv[]) {
    for (int i=1;i<argc;++i) {
        QDir baseDir(argv[i]);
        featureExtractGenderData(baseDir.filePath(femaleDir),femaleKey);
        featureExtractGenderData(baseDir.filePath(maleDir),maleKey);
    }
    return 0;
}


void featureExtractGenderData(QString dirPath, QString genderKey) {
    CData data(dirPath);
    QDir basePath = data.path();
    basePath.cdUp();
    QFile fileNameFile(basePath.filePath("files.txt"));
    fileNameFile.open(QFile::Append);
    bool needHeaders=false;
    QFile uniformFile(basePath.filePath("uniform.csv"));
    QFile regularFile(basePath.filePath("regular.csv"));
    if (uniformFile.exists() != regularFile.exists()) {
        uniformFile.open(QFile::WriteOnly);
        regularFile.open(QFile::WriteOnly);
        needHeaders = true;
    } else {
        if (!uniformFile.exists()) {
            needHeaders=true;
        }
        uniformFile.open(QFile::Append);
        regularFile.open(QFile::Append);
    }
    foreach (QFileInfo fileInfo, data()) {
        QTextStream fileNameStream(&fileNameFile);
        QTextStream uniformStream(&uniformFile);
        QTextStream regularStream(&regularFile);
        cv::Mat image = cv::imread(fileInfo.filePath().toStdString());
        cvtColor(image, image, CV_BGR2GRAY);
        GaussianBlur(image, image, Size(3,3), 5, 3, BORDER_CONSTANT); // tiny bit of smoothing is always a good idea
        CLBP lbp(image);
        if (needHeaders) {
            std::vector<QString> regularReader;
            regularReader.push_back("isFemale");
            for (size_t i=0; i<lbp.regularHistogram().size(); ++i) {
                regularReader.push_back(QString("F%1").arg(i));
            }
            std::vector<QString> uniformHeader;
            uniformHeader.push_back("isFemale");
            for (size_t i=0; i<lbp.uniformHistogram().size(); ++i) {
                uniformHeader.push_back(QString("F%1").arg(i));
            }

            CCommon::csvWrite(regularReader,regularStream);
            CCommon::csvWrite(uniformHeader,uniformStream);
            needHeaders=false;
        }
        uniformStream << genderKey << ", ";
        regularStream << genderKey << ", ";
        fileNameStream<< genderKey << ", ";
        CCommon::csvWrite(lbp.uniformNHistogram(),uniformStream);
        CCommon::csvWrite(lbp.regularNHistogram(),regularStream);
        fileNameStream << fileInfo.fileName() << "\r\n";
    }
}
