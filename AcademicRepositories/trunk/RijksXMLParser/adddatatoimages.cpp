#include "adddatatoimages.h"
#include <QDir>
#include <QStringList>

typedef QHash<QString, QHash<QString, QString> > Hashash;

class AddDataToImagesPrivate {
public:
    AddDataToImagesPrivate(){}
    Hashash hasher;
    QDir imageDir;
    QDir targetDir;
};

AddDataToImages::AddDataToImages(QHash<QString, QHash<QString, QString> > hasher, QDir imageDir, QDir targetDir):

    d(new AddDataToImagesPrivate())
{
    d->hasher = hasher;
    d->imageDir = imageDir;
    d->targetDir = targetDir;
}

AddDataToImages::~AddDataToImages()
{
    delete d;
}

void AddDataToImages::justDoIt(QStringList dataToPrepend)
{
    if (!d->imageDir.exists()) {
        qCritical("Image directory does not exist at %s",d->imageDir.absolutePath().toLatin1().constData());
        return;
    }
    if (!d->targetDir.exists())
        d->targetDir.mkpath(d->targetDir.absolutePath());
    foreach (QString inputFilename, d->hasher.keys()) {
        QHash<QString, QString> data = d->hasher.value(inputFilename);
        inputFilename.append(".jpg");
        QFileInfo from(d->imageDir, inputFilename);
        QString outputFilename = inputFilename;

        for (int idxData=0; idxData<dataToPrepend.count(); ++idxData) {
            QString dataName = dataToPrepend.value(idxData);
            QString dataValue = data.value(dataName);
            outputFilename.prepend(dataValue.append("_"));
        }
        QFileInfo to(d->targetDir, outputFilename);
        QFile::copy(from.absoluteFilePath(), to.absoluteFilePath());
    }
}

void AddDataToImages::justDoIt(QString dataToPrepend)
{
    justDoIt(QStringList()<<dataToPrepend);
}
