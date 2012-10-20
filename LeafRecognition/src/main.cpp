#include "leafrecognizer.h"
#include "datasetparser.h"
#include "extractleafcontour.h"

#include <QDir>
#include <QFileInfo>
#include <QVariantHash>
#include <QImage>

Q_DECLARE_METATYPE(QFileInfo)

int main(int & argc, char ** argv)
{
    qRegisterMetaType<QFileInfo>("QFileInfo");
    QDir dataDir("../flavia");
    QDir outputDir("../output");
    DatasetParser dp;
    ExtractLeafContour elc;
    QHash<int, QVariantList> dataset = dp.parseDataFolder(dataDir);
    QList<int> instanceUniqueIDList = dataset.keys();
    foreach (int instanceUniqueID, instanceUniqueIDList)
    {
        QVariantList instanceDescriptor = dataset[instanceUniqueID];
        QFileInfo instanceFileInfo = instanceDescriptor.first().value<QFileInfo>();
        Im instanceImage = cv::imread(instanceFileInfo.filePath().toAscii().constData());
        elc.segmentExteriorLeafContour(instanceImage);

    }

    QFileInfo resultFile(outputDir, "results.csv");
//    reportResults(dataset, resultFile.filePath());
    return 0;
}


//void reportResults(QVariantHash dataset, QString filePath)
//{
//    QStringList outputText;
//    QString seperator(",");
//    QStringList header;
//    header.clear();
//    header << "Class" << "Leaf Index";
//    bool headerSet= false;
//    QStringList classNameList = dataset.keys();
//    classNameList.sort();
//    for (int classInd=0; classInd<classNameList.count(); ++classInd)
//    {
//        QString className = classNameList[classInd];
//        QVariantHash classDescription = dataset.value(className).toHash();
//        QStringList leafIndexList = classDescription.keys();
//        leafIndexList.sort();
//        for (int leafInd=0; leafInd<leafIndexList.count(); ++leafInd)
//        {
//            QString leafIndex = leafIndexList[leafInd];
//            QStringList text;
//            QVariantHash leafFeatures = classDescription.value(leafIndex).toHash();
//            text << className << leafIndex;
//            QStringList leafFeatureList = leafFeatures.keys();
//            leafFeatureList.sort();
//            for (int i = 0; i<leafFeatureList.count(); ++i)
//            {
//                if (!headerSet)
//                {
//                    header << leafFeatureList[i];
//                }
//                float featureVal = leafFeatures.value(leafFeatureList[i]).toFloat();
//                text << QString::number(featureVal);
//            }
//            headerSet = true;
//            outputText << text.join(seperator);
//        }
//        outputText.append("\r\n");
//    }
//    QString text = QString("Leaf Feature Set\r\n").append(header.join(seperator).append("\r\n")).append(outputText.join("\r\n"));
//    QFile file(filePath);
//    if(file.open(QIODevice::WriteOnly))
//    {
//        QDataStream stream(&file);
//        stream << text;
//    }
//}
