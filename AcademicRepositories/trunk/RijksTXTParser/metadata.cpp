#include "metadata.h"

#include <QFileInfo>
#include <QStringList>
typedef QHash<QString, QString> QStringHash;
//typedef QHash<int, QStringHash> Hashash;
typedef QList<QStringHash> Hashash;
class MetaDataPrivate {
public:
    MetaDataPrivate() {}
    Hashash hasher;
    QFileInfo metaTxtFile;
    QStringList headers;
    bool parseTxt() {
        //read from metaTxtFile into hasher
        QFile txtFile(metaTxtFile.absoluteFilePath());
        if (txtFile.open(QFile::ReadOnly)) {
            QString header = txtFile.readLine(); // header
            headers = header.split("\t");
            int nHeaders = headers.count();
            while (!txtFile.atEnd()) {
                QString sample = txtFile.readLine();
                QStringList features = sample.split("\t");
                QString filename = features.first();
                if (features.count()!=nHeaders) {
                    qWarning("Header / Feature count does not match!! \n%s\n%s",header.toLatin1().constData(), sample.toLatin1().constData());
                }
                QStringHash sampleHash;
                for(int i=0; i<nHeaders; ++i) {
                    sampleHash.insert(headers[i],features[i]);
                }
                hasher.insert(hasher.count(), sampleHash);
            }
            return true;
        }
        return false;
    }
};

Metadata::Metadata():
    d(new MetaDataPrivate())
{
}

Metadata*Metadata::generate(QFileInfo txtFileInfo)
{
    Metadata* t = new Metadata;
    t->d->metaTxtFile = txtFileInfo;
    if (t->d->parseTxt()) {
        return t;
    } else {
        delete t;
        return 0;
    }
}

Metadata::~Metadata()
{
    delete d;
}

QStringList Metadata::headers() const
{
    return d->headers;
}

int Metadata::count() const
{
    return d->hasher.count();
}

QString Metadata::at(int index, QString header)
{
    return d->hasher.value(index).value(header);
}
