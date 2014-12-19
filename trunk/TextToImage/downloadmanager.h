#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H
#include <QtNetwork>
#include <QNetworkAccessManager>
class DownloadManager : public QObject
{
    Q_OBJECT
    QNetworkAccessManager manager;
    QList<QNetworkReply *> currentDownloads;
    QDir _downloadDir;

public:
    DownloadManager(QString downloadPath);
    QString saveFileName(const QUrl &url);
    bool saveToDisk(const QString &filename, QIODevice *data);

public slots:
    void doDownload(const QUrl &url);

private slots:
    void downloadFinished(QNetworkReply *reply);
};


#endif // DOWNLOADMANAGER_H
