#include "facelookuptable.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDateTime>
#include <QRect>
#include <QDir>
FaceLookupTable::FaceLookupTable()
{
    QFileInfo outInfo("out.txt");
    if (outInfo.exists()) {
        QFile::copy(outInfo.filePath(), QString("out_%1.txt").arg(QDateTime::currentDateTime().toString()));
    }
    streamFile = new QFile(outInfo.filePath());
    if (!streamFile->open(QFile::WriteOnly))
        qFatal("Failed to open %s", outInfo.absoluteFilePath().constData());
}

void FaceLookupTable::addFile(QFileInfo input, QList<QRect> destRects, QFileInfo destFileInfo, double scaleBackFactor)
{
    if (destRects.count()>1) {
        for (int i=0; i< destRects.count(); ++i) {
            QRect destRect = destRects.at(i);
            QRect destRectScaled(destRect.topLeft()*scaleBackFactor, destRect.bottomRight()*scaleBackFactor);
            QString destString = destFileInfo.absolutePath();
            destString.append(QDir::separator());
            destString.append(destFileInfo.completeBaseName());
            destString.append("_");
            destString.append(QString::number(i));
            destString.append(".");
            destString.append(destFileInfo.suffix());
            QFileInfo rectFileInfo(destString);
            QTextStream stream(streamFile);
            stream
                    << input.baseName() << "\t"
                    << destRectScaled.left() << "\t"
                    << destRectScaled.top() << "\t"
                    << destRectScaled.width() << "\t"
                    << destRectScaled.height() << "\t"
                    << rectFileInfo.fileName() << "\r\n"
                    ;
        }
    } else if (destRects.count()==1){
        QRect destRect = destRects.first();
        QRect destRectScaled(destRect.topLeft()*scaleBackFactor, destRect.bottomRight()*scaleBackFactor);
        QTextStream stream(streamFile);
        stream
                << input.baseName() << "\t"
                << destRectScaled.left() << "\t"
                << destRectScaled.top() << "\t"
                << destRectScaled.width() << "\t"
                << destRectScaled.height() << "\t"
                << destFileInfo.fileName() << "\r\n"
                ;
    }
}

void FaceLookupTable::save()
{

    foreach (QFileInfo input, lookupTable.keys()) {

    }
}

