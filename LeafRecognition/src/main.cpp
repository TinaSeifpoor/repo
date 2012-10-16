#include "leafrecognizer.h"


#include <QDir>
#include <QFileInfo>

int main()
{
    QDir dir("../data");
    QList<QFileInfo> imageFileList = dir.entryInfoList(QStringList()<<QString("?g?.tif"), QDir::Files, QDir::Name);
    LeafRecognizer lr;
    foreach (QFileInfo imageFile, imageFileList)
    {
        cv::Mat im = cv::imread(imageFile.absoluteFilePath().toAscii().constData());
        lr.recognize(im);
    }

    return 0;
}
