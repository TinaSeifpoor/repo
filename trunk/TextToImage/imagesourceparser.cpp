#include "imagesourceparser.h"

ImageSourceParser::ImageSourceParser(QRegExp begin, QRegExp end, QObject *parent) :
    _begin(begin), _end(end), QObject(parent)
{
}

void ImageSourceParser::urlSource(QString source)
{
    int idxMatch = source.indexOf(_begin);
    while (idxMatch!=-1) {
        idxMatch+=45;
        QString imageUrlBegin = source.mid(idxMatch);
        int idxMatchEnd = imageUrlBegin.indexOf(_end);
        emit download(QUrl::fromEncoded(imageUrlBegin.left(idxMatchEnd).toLatin1()));
        source = imageUrlBegin.mid(idxMatchEnd);
        idxMatch = source.indexOf(_begin);
    }
}
