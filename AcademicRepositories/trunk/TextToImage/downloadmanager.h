#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QSignalMapper>
class DownloadManager : public QObject
{
    Q_OBJECT
    QNetworkAccessManager* manager;
    QList<QNetworkReply *> currentDownloads;
    QList<QObject *> finishedDownloads;
    QDir _downloadDir;
    QSignalMapper mapper;

public:
    DownloadManager(QNetworkAccessManager* manager, QString downloadPath);
    QString saveFileName(const QUrl &url);
    bool saveToDisk(const QString &filename, QIODevice *data);

public slots:
    void doDownload(const QUrl &url);

private slots:
    void downloadFinished(QNetworkReply *reply);
    void downloadTimeout(QObject *reply);
};


#endif // DOWNLOADMANAGER_H
