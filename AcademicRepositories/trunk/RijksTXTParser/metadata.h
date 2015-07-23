#ifndef METADATA_H
#define METADATA_H

#include <QHash>
#include <QFileInfo>
class MetaDataPrivate;
class Metadata
{
    MetaDataPrivate* d;
    Metadata();
public:
    static Metadata* generate(QFileInfo txtFileInfo);
    ~Metadata();
    QStringList headers() const;
    int count() const;
    QString at(int index, QString header);
};

#endif // METADATA_H
