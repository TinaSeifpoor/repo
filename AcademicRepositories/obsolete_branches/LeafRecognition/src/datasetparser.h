#ifndef DATASETPARSER_H
#define DATASETPARSER_H

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QVariantHash>

class DatasetParser
{
public:
    DatasetParser();
    QHash<int, QVariantList> parseDataFolder(QDir datasetFolder);
private:
    QVariantList parseDataFile(QFileInfo dataFileInfo);
    QHash<int, int> parseInstanceUniqueID (QString instanceUniqueIDPlain, int classID);
    QHash<int, QVariantList> matchUniqueIDWithImage(QVariantList, QList<QFileInfo>);

};

#endif // DATASETPARSER_H
