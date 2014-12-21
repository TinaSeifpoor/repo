#ifndef GOOGLEIMAGEPARSER_H
#define GOOGLEIMAGEPARSER_H

#include <QObject>
#include <QUrl>
#include <QRegExp>
class ImageSourceParser : public QObject
{
    QString _begin, _end;
    Q_OBJECT
public:
    explicit ImageSourceParser(QString begin, QString end, QObject *parent = 0);

signals:

    void download(QUrl);
public slots:
    void urlSource(QString source);
};

#endif // GOOGLEIMAGEPARSER_H
