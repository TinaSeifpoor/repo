#include <QApplication>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include "adddatatoimages.h"
//#define WriteIndividualFiles
//#define WriteReport
//#define trace
#define MakeCopy
#define PrependDate
QString between(QString source, QString begin, QString end) {
    QString beginString;
    {
        QStringList contents = source.split(begin);
        Q_ASSERT(contents.count()>1);
        beginString = contents.last();
    }
    QString endString;
    {
        QStringList contents = beginString.split(end);
        Q_ASSERT(contents.count()>1);
        endString = contents.first();
    }
    return endString;
}

void writeKeyVal(QFileInfo xmlFileInfo, QString key, QString val) {
    QDir keyDir = xmlFileInfo.dir();
    keyDir.cdUp();
    if (!keyDir.exists(key))
        keyDir.mkdir(key);
    keyDir.cd(key);
    QFileInfo valInfo(keyDir, xmlFileInfo.fileName());
    QFile valFile(valInfo.absoluteFilePath());
    valFile.open(QFile::WriteOnly);
    valFile.write(val.toLatin1());
    valFile.close();
}


QHash<QString, QHash<QString, QString> > hasher;
QHash<QString,int> keyIndices;
int nextIndex=0;

void reportHasher() {
    QByteArray report;
    QTextStream stream(&report);
    stream << "filename";
    for (int i=0; i<nextIndex;++i) {
        stream << "\t" << keyIndices.key(i);
    }
    foreach (QString filename, hasher.keys()) {
        QHash<QString, QString> hash = hasher.value(filename);
        stream << filename;
        for (int i=0; i<nextIndex; ++i) {
            stream << "\t" << hash.value(keyIndices.key(i));
        }
        stream << "\n";
    }
    QFile reportFile("../report.tab");
    reportFile.open(QFile::WriteOnly);
    reportFile.write(report);
    reportFile.close();
}

void parseXMLInfo(QFileInfo xmlFileInfo, QString xmlFileContents) {
    QString metaData = between(xmlFileContents, "<oai_dc:dc>", "</oai_dc:dc>");
    metaData.remove("\t");
    metaData.remove("\n");
    metaData.remove("\r");
    QStringList metaDataPieces = metaData.split("<dc:", QString::SkipEmptyParts);
 #ifdef trace
    qDebug("File: %s", xmlFileInfo.filePath().toLatin1().constData());
#endif

    QHash<QString,QString> keyVal;
    foreach (QString metaDataPiece, metaDataPieces) {
        QStringList contents = metaDataPiece.split(">");
        QString key = contents.takeFirst();
        key = key.remove("/").trimmed();
        QString val = contents.takeFirst();
        val = val.split("</").takeFirst();
        if (key.contains("date")) {
            val = val.split("-").takeFirst();
            if (val.toInt()==0) {
                QStringList valContents = val.split(" ", QString::SkipEmptyParts);
                while (!valContents.isEmpty()) {
                    if (valContents.first().toInt()) {
                        val = valContents.takeFirst();
                        break;
                    }
                    else
                        valContents.removeFirst();
                }
            }
            val = QString::number(val.toInt());
        }
        if (!keyIndices.contains(key))
            keyIndices.insert(key,nextIndex++);
        keyVal.insert(key,val);

#ifdef trace
        qDebug("%s",metaDataPiece.toLatin1().constData());
#endif
    }
    hasher.insert(xmlFileInfo.baseName(), keyVal);
#ifdef WriteIndividualFiles
    foreach (QString key, keyVal.keys())
        writeKeyVal(xmlFileInfo, key, keyVal.value(key));
#endif
}

void splitXMLFile(QFileInfo info) {
    QFile file(info.absoluteFilePath());
    if (file.open(QFile::ReadOnly)) {
        QTextStream stream(&file);
        QString xmlFileContents = stream.readAll();
        parseXMLInfo(info, xmlFileContents);
    } else {
        qWarning("Failed to read: %s", info.filePath().toLatin1().constData());
    }
}

QList<QFileInfo> parseXMLFiles(QDir dirToParseFrom=QDir::current()) {
    Q_ASSERT(dirToParseFrom.exists());
    Q_ASSERT(dirToParseFrom.isReadable());
    QList<QFileInfo> fileList;

    QList<QFileInfo> d = dirToParseFrom.entryInfoList(QDir::NoDotAndDotDot|QDir::AllDirs);
    foreach (QFileInfo dF, d)
        fileList << parseXMLFiles(dF.absoluteFilePath());
    QList<QFileInfo> f = dirToParseFrom.entryInfoList(QStringList() << "*.xml", QDir::AllEntries|QDir::Files);
    foreach (QFileInfo fF, f)
        splitXMLFile(fF);
    return fileList << f;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (argc>1)
        QDir::setCurrent(argv[1]);
#if defined(WriteReport)||defined(WriteIndividualFiles)||defined(PrependDate)
    parseXMLFiles(); // outputs hasher
#endif
#ifdef WriteReport
    reportHasher();
#endif
    QDir baseDir = QDir::current();
    baseDir.cdUp();
    AddDataToImages adti(hasher, baseDir.filePath("jpg2"),baseDir.filePath("typeDate2"));
    adti.justDoIt(QStringList()<<"date"<<"type");
    return 0;
}
