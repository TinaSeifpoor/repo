#include "leafrecognizer.h"


#include <QDir>
#include <QFileInfo>
#include <QVariantHash>
#include <QImage>

void reportResults(QVariantHash dataset, QString filePath);
int main(int & argc, char ** argv)
{
    typedef cv::Mat image;
    qRegisterMetaType<image>("image");
    QDir dataDir("../data");
    QDir outputDir("../output");
    QList<QFileInfo> imageFileList = dataDir.entryInfoList(QStringList()<<QString("?g?.tif"), QDir::Files, QDir::Name);
    QVariantHash dataset;
    foreach (QFileInfo imageFile, imageFileList)
    {
        QString className = imageFile.baseName().left(1);
        cv::Mat im = cv::imread(imageFile.absoluteFilePath().toAscii().constData());
        cv::Mat imOut;
        LeafRecognizer lr(im);
        QVariantHash leafFeatures = lr.getLeafFeatures(&imOut);
        QVariantHash classDescription;
        if (dataset.keys().contains(className))
        {
            classDescription = dataset.value(className).toHash();
        }
        QString leafIndex = QString::number(classDescription.keys().count());
        QFileInfo outputImageFile(outputDir, QString("%1o%2.jpg").arg(className).arg(leafIndex));
        if (!outputDir.exists())
            outputDir.mkpath(outputDir.absolutePath());
        cv::imwrite(outputImageFile.filePath().toAscii().constData(), imOut);
        classDescription.insert(QString::number(classDescription.keys().count()), leafFeatures);
        dataset.remove(className);
        dataset.insert(className, classDescription);
    }
    QFileInfo resultFile(outputDir, "results.csv");
    reportResults(dataset, resultFile.filePath());
    return 0;
}


void reportResults(QVariantHash dataset, QString filePath)
{
    QStringList outputText;
    QString seperator(",");
    QStringList header;
    header.clear();
    header << "Class" << "Leaf Index";
    bool headerSet= false;
    QStringList classNameList = dataset.keys();
    classNameList.sort();
    for (int classInd=0; classInd<classNameList.count(); ++classInd)
    {
        QString className = classNameList[classInd];
        QVariantHash classDescription = dataset.value(className).toHash();
        QStringList leafIndexList = classDescription.keys();
        leafIndexList.sort();
        for (int leafInd=0; leafInd<leafIndexList.count(); ++leafInd)
        {
            QString leafIndex = leafIndexList[leafInd];
            QStringList text;
            QVariantHash leafFeatures = classDescription.value(leafIndex).toHash();
            text << className << leafIndex;
            QStringList leafFeatureList = leafFeatures.keys();
            leafFeatureList.sort();
            for (int i = 0; i<leafFeatureList.count(); ++i)
            {
                if (!headerSet)
                {
                    header << leafFeatureList[i];
                }
                float featureVal = leafFeatures.value(leafFeatureList[i]).toFloat();
                text << QString::number(featureVal);
            }
            headerSet = true;
            outputText << text.join(seperator);
        }
        outputText.append("\r\n");
    }
    QString text = QString("Leaf Feature Set\r\n").append(header.join(seperator).append("\r\n")).append(outputText.join("\r\n"));
    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        stream << text;
    }
}
