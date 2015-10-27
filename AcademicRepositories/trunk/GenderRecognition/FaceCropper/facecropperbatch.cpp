#include "facecropperbatch.h"
#include "facecropper.h"
#include <QApplication>
#include <QStringList>
#include <QDir>
#include <QImageReader>
#include <QDebug>
#include <QMetaMethod>
#include "facelookuptable.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("FaceCropper");
    QApplication::setApplicationVersion("0.1");
    QApplication::setOrganizationName("Katiksiz");

    FaceCropperBatch batch;
    QMetaObject::invokeMethod(&batch, "go", Qt::QueuedConnection);
    return a.exec();
}


FaceCropperBatch::FaceCropperBatch():
    faceCropper(new FaceCropper())
{

}

void FaceCropperBatch::go()
{
    QStringList arguments = qApp->arguments();
    if (arguments.count()<3) {
        showUsage();
        QMetaObject::invokeMethod(qApp, "quit", Qt::DirectConnection);
        return;
    }
    QString sourceString = arguments.at(1);
    QString destString = arguments.at(2);

    QDir sourceDir(sourceString);
    QDir destDir(destString);
    QStringList nameFilters;
    foreach (QByteArray format, QImageReader::supportedImageFormats()) {

        nameFilters << "*."+format;
    }
    QFileInfoList sourceInfoList = findFilesRecursively(sourceDir, nameFilters);
    qDebug() << sourceInfoList.count() << " files found!";
    FaceLookupTable facelookupTable;
    foreach (QFileInfo sourceInfo, sourceInfoList) {
        QImage sourceImage(sourceInfo.absoluteFilePath());
        QImage scaledSourceImage = sourceImage.scaled(225,225,Qt::KeepAspectRatio);
        int sourceWidth = sourceImage.width();
        int destWidth = scaledSourceImage.width();
        double scaleBackFactor = (double)sourceWidth/destWidth; // as we keep aspect ratio, this is sufficient to scale rectangle back
        qDebug() << sourceInfo.fileName();
        QList<QRect> destRects;
        QFileInfo destFileInfo = makeDestFileInfo(sourceDir, sourceInfo, destDir);
        if (faceCropper->crop(scaledSourceImage,destRects)) {
//            facelookupTable.addFile(sourceInfo, destRects, destFileInfo, scaleBackFactor);
            if (destRects.count()>1) {
                for (int i=0; i< destRects.count(); ++i) {
                    QRect destRect = destRects.at(i);
                    QRect destRectScaled(destRect.topLeft()*scaleBackFactor, destRect.bottomRight()*scaleBackFactor);
                    QImage destImage = sourceImage.copy(destRectScaled);
                    QString destString = destFileInfo.absolutePath();
                    destString.append(QDir::separator());
                    destDir.mkpath(destString);
                    destString.append(destFileInfo.completeBaseName());
                    destString.append("_");
                    destString.append(QString::number(i));
                    destString.append(".");
                    destString.append(destFileInfo.suffix());
                    destImage.save(destString);
                }
            } else if (destRects.count()==1){
                QRect destRect = destRects.first();
                QRect destRectScaled(destRect.topLeft()*scaleBackFactor, destRect.bottomRight()*scaleBackFactor);
                QImage destImage = sourceImage.copy(destRectScaled);
                destDir.mkpath(destFileInfo.absolutePath());
                destImage.save(destFileInfo.absoluteFilePath());
            }
        }
    }
    QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
}

QFileInfo FaceCropperBatch::makeDestFileInfo(QDir sourceDir, QFileInfo sourceFileInfo, QDir destDir) const
{
    return destDir.filePath(sourceDir.relativeFilePath(sourceFileInfo.absoluteFilePath()));
}

void FaceCropperBatch::showUsage() const
{
    qDebug("Usage: FaceCropper.exe \"SourceDirectory\" \"DestinationDirectory\"");
    qDebug("Make sure \"cascadeXML\", and CascadeDetector files exist in working directory for detection.");
}

QList<QFileInfo> FaceCropperBatch::findFilesRecursively(QDir dir, QStringList nameFilters) const
{
    QList<QFileInfo> foundFiles;
    foreach (QString dirName, dir.entryList(QStringList(), QDir::NoDotAndDotDot|QDir::Dirs)) {
        QDir subDir(dir);
        subDir.cd(dirName);
        foundFiles << findFilesRecursively(subDir, nameFilters);
    }
    QFileInfoList currentFiles = dir.entryInfoList(nameFilters, QDir::NoDotAndDotDot|QDir::Files);
    foundFiles << currentFiles;
    return foundFiles;
}


