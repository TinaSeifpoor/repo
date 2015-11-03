#include <QCoreApplication>
#include "genderizerdata.h"
#include "splitdata.h"
#include <QDir>
#include <QFile>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    GenderizerData data(argv[1]);
    QStringList filters;
    for (int i=3; i<argc; ++i)
        filters << argv[i];
    QString dbPath = argv[2];
    SplitData files(dbPath, filters);

    QDir maleDir(dbPath);
    maleDir.mkpath("male");
    maleDir.cd("male");
    QDir femaleDir(dbPath);
    femaleDir.mkpath("female");
    femaleDir.cd("female");
    QDir otherDir(dbPath);
    otherDir.mkpath("other");
    otherDir.cd("other");

    foreach (QFileInfo dbFileInfo, files()) {
        Gender gender = data.queryPath(dbFileInfo.filePath());
        QDir destination;
        switch (gender) {
        case Male:
            destination=maleDir;
            break;
        case Female:
            destination=femaleDir;
            break;
        default:
            destination=otherDir;
            break;
        }
        QString destinationPath = destination.filePath(dbFileInfo.fileName());
        if (QFile::copy(dbFileInfo.filePath(), destinationPath)) {
            qDebug("Successfully copied %s to %s", dbFileInfo.filePath().toLatin1().constData(), destinationPath.toLatin1().constData());
        } else {
            qDebug("Failed to copy %s to %s", dbFileInfo.filePath().toLatin1().constData(), destinationPath.toLatin1().constData());
        }
    }

    return 1;
}
