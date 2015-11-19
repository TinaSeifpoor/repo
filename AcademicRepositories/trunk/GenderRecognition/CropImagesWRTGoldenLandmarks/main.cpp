#include <QCoreApplication>
#include "cihanlib.h"
#include <QDir>
#include "opencv2/opencv.hpp"
// argv = "D:\Downloads\10k Adult Faces\10kfaces\10k US Adult Faces Database\female" "D:\Downloads\10k Adult Faces\10kfaces\10k US Adult Faces Database\female_aligned" "D:\Downloads\10k Adult Faces\10kfaces\10k US Adult Faces Database\male" "D:\Downloads\10k Adult Faces\10kfaces\10k US Adult Faces Database\male_aligned" "D:\Downloads\lfw\female" "D:\Downloads\lfw\female_aligned" "D:\Downloads\lfw\male" "D:\Downloads\lfw\male_aligned"
int main(int argc, char *argv[])
{
    using namespace CihanLib;
    QCoreApplication a(argc, argv);
    CGoldenLandmark golden(argv[1]);
    golden.load();
    for (int i=2; i<argc; i+=2) {
        CData wildData(argv[i]);
        QDir target(argv[i+1]);
        target.mkpath(target.path());
        foreach (QFileInfo wildInfo, wildData()) {
            CLandmark landmark(wildInfo);
            if (landmark.isValid()) {
                QString targetFilePath = target.filePath(wildInfo.fileName());
                cv::imwrite(targetFilePath.toStdString(), landmark.alignTo(golden));
            }
        }
    }
    return a.exec();
}
