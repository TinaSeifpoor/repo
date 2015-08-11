#ifndef FACECROPPERBATCH_H
#define FACECROPPERBATCH_H

class FaceCropper;
#include <QList>
#include <QObject>
class QFileInfo;
class QDir;
class QStringList;
class FaceCropperBatch : public QObject
{
    Q_OBJECT
public:
    FaceCropperBatch();
    void showUsage() const;
    QList<QFileInfo> findFilesRecursively(QDir dir, QStringList nameFilters) const;
    QFileInfo makeDestFileInfo(QDir sourceDir, QFileInfo sourceFileInfo, QDir destDir) const;
public slots:
    void go();
private:
    FaceCropper*faceCropper;
};

#endif // FACECROPPERBATCH_H
