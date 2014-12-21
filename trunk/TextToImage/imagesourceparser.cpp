#include "imagesourceparser.h"
#include <QFile>
ImageSourceParser::ImageSourceParser(QString begin, QString end, QObject *parent) :
    _begin(begin), _end(end), QObject(parent)
{
}

void ImageSourceParser::urlSource(QString source)
{
    QFile sourceFile("source.txt");
    sourceFile.open(QFile::WriteOnly);
    sourceFile.write(source.toLatin1());
    sourceFile.close();
    int idxMatch = source.indexOf(_begin);
    int beginLength = _begin.length();
    while (idxMatch!=-1) {
        idxMatch+=beginLength;
        QString imageUrlBegin = source.mid(idxMatch);
        int idxMatchEnd = imageUrlBegin.indexOf(_end);
        emit download(QUrl::fromEncoded(imageUrlBegin.left(idxMatchEnd).toLatin1()));
        source = imageUrlBegin.mid(idxMatchEnd);
        idxMatch = source.indexOf(_begin);
    }
}
