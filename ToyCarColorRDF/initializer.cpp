#include "initializer.h"
#include "source.h"
#include <QFileInfo>
#include <QDir>
#include "opencv2/opencv.hpp"
Q_DECLARE_METATYPE(cv::Mat)

Source* Initializer::getSource() {
    QDir imgDir("../toy_car_lear/imstdsize");
    QStringList classNameList = imgDir.entryList(QDir::NoDotAndDotDot | QDir::Dirs);
    QList<Sample> samples;
    foreach (QString className, classNameList) {
        QDir classDir(imgDir);
        classDir.cd(className);
        QFileInfoList imageFileInfoList = classDir.entryInfoList(QStringList()<<"*.png", QDir::Files);
        foreach (QFileInfo imageFileInfo, imageFileInfoList) {
            cv::Mat image = cv::imread(imageFileInfo.filePath().toStdString());
            Sample s;
            s.sampleClass = classDir.dirName().toInt();
            s.sampleId = imageFileInfo.fileName();
            s.sampleSource = QVariant::fromValue<cv::Mat>(image);
            samples << s;
        }
    }
    return new Source(samples);
}
