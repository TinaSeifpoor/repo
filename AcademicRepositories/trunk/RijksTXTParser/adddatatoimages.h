#ifndef ADDDATATOIMAGES_H
#define ADDDATATOIMAGES_H

#include <QHash>
class QDir;
class AddDataToImagesPrivate;
class AddDataToImages
{
public:
    AddDataToImages(QHash<QString, QHash<QString, QString> > hasher, QDir  imageDir, QDir targetDir);
    ~AddDataToImages();
    void justDoIt(QStringList dataToPrepend);
    void justDoIt(QString dataToPrepend);
private:
    AddDataToImagesPrivate*d;
};

#endif // ADDDATATOIMAGES_H
