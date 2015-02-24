#include "datasetparser.h"
#include <Common.h>
typedef QHash<int,QString> a;
typedef QHash<int,int> b;

Q_DECLARE_METATYPE(a)
Q_DECLARE_METATYPE(b)
Q_DECLARE_METATYPE(QFileInfo)

DatasetParser::DatasetParser()
{
    qRegisterMetaType<QFileInfo>("QFileInfo");
    qRegisterMetaType<QHash<int,QString> >("QHash<int,QString>");
    qRegisterMetaType<QHash<int,int> >("QHash<int,int>");


}

QHash<int, QVariantList> DatasetParser::parseDataFolder(QDir datasetFolder)
{
    QFileInfo dataFileInfo(datasetFolder, datasetDescriptorFileName);
    QVariantList datasetDescriptor = this->parseDataFile(dataFileInfo);
    QList<QFileInfo> imageFileInfoList = datasetFolder.entryInfoList(extentions, QDir::Files, QDir::Name);
    return this->matchUniqueIDWithImage(datasetDescriptor, imageFileInfoList);
}

QVariantList DatasetParser::parseDataFile(QFileInfo dataFileInfo)
{
    QVariantList datasetDescriptor;
    QHash<int,int> instanceDescriptor;
    QHash<int,QString> classDescriptor;
    QFile dataFile(dataFileInfo.filePath());
    QString datasetDescriptionPlain;
    if (dataFile.open(QIODevice::ReadOnly))
        datasetDescriptionPlain = dataFile.readAll();
    else
    {
        qDebug(QString("Can't open file: %1").arg(dataFileInfo.absoluteFilePath()).toAscii());
        return QVariantList();
    }

    QStringList instanceDescriptionPlainList = datasetDescriptionPlain.split(instanceSeperator);
    QStringList headerList = instanceDescriptionPlainList.takeFirst().split(headerSeperator);
    int instanceUniqueIDIndex = headerList.indexOf(instanceUniqueIDHeader);
    int classNameIndex = headerList.indexOf(classNameHeader);
    int classIDIndex = headerList.indexOf(classIDHeader);

    foreach (QString instanceDescriptionPlain, instanceDescriptionPlainList)
    {
        QStringList instanceDescriptionList = instanceDescriptionPlain.split(headerSeperator);
        QString className = instanceDescriptionList[classNameIndex];
        int classID = instanceDescriptionList[classIDIndex].toInt();
        if (!classDescriptor[classID].isEmpty())
        {
            if (classDescriptor[classID] != className)
            {
                qDebug(QString("Class ID %1 is matched to classes with names %2 & %3").arg(classID).arg(classDescriptor[classIDIndex]).arg(className).toAscii());
            }
        }
        else
            classDescriptor[classID] = className;
        QString instanceUniqueID = instanceDescriptionList[instanceUniqueIDIndex];
        instanceDescriptor.unite(this->parseInstanceUniqueID(instanceUniqueID, classID));
    }
    datasetDescriptor << QVariant::fromValue<QHash<int,int> >(instanceDescriptor) << QVariant::fromValue<QHash<int,QString> >(classDescriptor);
    return datasetDescriptor;

}

QHash<int, int> DatasetParser::parseInstanceUniqueID(QString instanceUniqueIDPlain, int classID)
{
    QHash<int, int> instanceUniqueIDList;
    QStringList instanceUniqueIDEach = instanceUniqueIDPlain.split(instanceUniqueIDSeperatorTakeEach);
    foreach (QString instanceUniqueID, instanceUniqueIDEach)
    {
        QStringList instanceUniqueIDBetween = instanceUniqueID.split(instanceUniqueIDSeperatorTakeBetween);
        if (instanceUniqueIDBetween.count()>1)
            for (int i=instanceUniqueIDBetween.first().toInt(); i<=instanceUniqueIDBetween.last().toInt(); ++i)
                instanceUniqueIDList[i] = classID;
        else if (!instanceUniqueIDBetween.isEmpty())
            instanceUniqueIDList[instanceUniqueIDBetween.first().toInt()] = classID;
    }
    return instanceUniqueIDList;
}

QHash<int, QVariantList > DatasetParser::matchUniqueIDWithImage(QVariantList datasetDescriptor, QList<QFileInfo> imageFileInfoList)
{
    QHash<int, QVariantList> dataset;
    QHash<int,int> instanceDescriptor = datasetDescriptor.first().value<QHash<int,int> >();
    QHash<int,QString> classDescriptor = datasetDescriptor[1].value<QHash<int,QString> >();
    foreach (QFileInfo imageFileInfo, imageFileInfoList)
    {
        int imageFileID = imageFileInfo.baseName().toInt();
        int classID = instanceDescriptor[imageFileID];
        QVariantList instanceDescription;
        instanceDescription << QVariant::fromValue<QFileInfo>(imageFileInfo) << classID << classDescriptor[classID];
        dataset[imageFileID] = instanceDescription;
    }
    return dataset;
}
