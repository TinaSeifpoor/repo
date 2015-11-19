#include <opencv2/opencv.hpp>
#include "cihanlib.h"
#include <QFileInfo>
#include <QDir>
using namespace cv;
using CihanLib::CData;
using CihanLib::CLBP;
#include <QTextStream>
template <typename tt>
    QTextStream & csvWrite(std::vector<tt> valueVector, QTextStream& stream) {
        for (size_t i=0; i<valueVector.size()-1; ++i) {
            stream << valueVector.at(i) << ", ";
        }
        stream << valueVector.at(valueVector.size()-1) << "\r\n";
        return stream;
    }

int main(int argc, const char *argv[]) {
    foreach (CData data, CData::multiData(argc,argv)) {
        QDir basePath = data.path();
        basePath.cdUp();
        QFile fileNameFile(basePath.filePath("files.txt"));
        fileNameFile.open(QFile::WriteOnly);
        QTextStream fileNameStream(&fileNameFile);
        QFile uniformFile(basePath.filePath("uniform.csv"));
        uniformFile.open(QFile::WriteOnly);
        QTextStream uniformStream(&uniformFile);
        QFile regularFile(basePath.filePath("regular.csv"));
        regularFile.open(QFile::WriteOnly);
        QTextStream regularStream(&regularFile);
        foreach (QFileInfo fileInfo, data()) {
            cv::Mat image = cv::imread(fileInfo.filePath().toStdString());
            cvtColor(image, image, CV_BGR2GRAY);
            GaussianBlur(image, image, Size(3,3), 5, 3, BORDER_CONSTANT); // tiny bit of smoothing is always a good idea
            CLBP lbp(image);
            uniformStream << "0, ";
            regularStream << "0, ";
            csvWrite(lbp.uniformNHistogram(),uniformStream);
            csvWrite(lbp.regularNHistogram(),regularStream);
            fileNameStream << fileInfo.fileName() << "\r\n";
        }
    }
    return 0;
}
