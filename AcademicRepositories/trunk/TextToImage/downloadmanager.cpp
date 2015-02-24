#include "downloadmanager.h"

DownloadManager::DownloadManager(QNetworkAccessManager *manager, QString downloadPath):_downloadDir(downloadPath), manager(manager)
{
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            SLOT(downloadFinished(QNetworkReply*)));
    connect(&mapper, SIGNAL(mapped(QObject*)),
            SLOT(downloadTimeout(QObject*)));
}

void DownloadManager::doDownload(const QUrl &url)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);
    QTimer* timeoutTimer = new QTimer;
    connect(timeoutTimer, SIGNAL(timeout()), &mapper, SLOT(map()));
    mapper.setMapping(timeoutTimer,reply);
    timeoutTimer->setSingleShot(true);
    if (qApp->argc()>3)
        timeoutTimer->start(QString(qApp->argv()[3]).toInt());
    else
        timeoutTimer->start(20000);
    currentDownloads.append(reply);
}

QString DownloadManager::saveFileName(const QUrl &url)
{
    QFileInfo urlInfo(url.path());
    QFileInfo fileInfo(_downloadDir, urlInfo.fileName());
    fileInfo.dir().mkpath(fileInfo.absolutePath());
    QString basename = fileInfo.baseName();
    if (basename.isEmpty())
        basename = "download";

    if (QFile::exists(basename)) {
        // already exists, don't overwrite
        int i = 0;
        basename += '_';
        while (QFile::exists(basename + QString::number(i)))
            ++i;

        basename += QString::number(i);
    }
    basename.append(".").append(fileInfo.completeSuffix());
    QFileInfo cFileInfo(fileInfo.dir(), basename);
    return cFileInfo.filePath();
}

bool DownloadManager::saveToDisk(const QString &filename, QIODevice *data)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        fprintf(stderr, "Could not open %s for writing: %s\n",
                qPrintable(filename),
                qPrintable(file.errorString()));
        return false;
    }

    file.write(data->readAll());
    file.close();

    return true;
}

void DownloadManager::downloadFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    if (reply->error()) {
        fprintf(stderr, "Download of %s failed: %s\n",
                url.toEncoded().constData(),
                qPrintable(reply->errorString()));
    } else {
        QString filename = saveFileName(url);
        if (saveToDisk(filename, reply))
            printf("Download of %s succeded (saved to %s)\n",
                   url.toEncoded().constData(), qPrintable(filename));
    }

    currentDownloads.removeAll(reply);
    reply->deleteLater();
    finishedDownloads.append(reply);

    if (currentDownloads.isEmpty())
        //   all downloads finished
        QCoreApplication::instance()->quit();
}

void DownloadManager::downloadTimeout(QObject *reply)
{
    if (!finishedDownloads.contains(reply)) {
        QNetworkReply* networkReply = qobject_cast<QNetworkReply*>(reply);
        if (networkReply) {
            if (networkReply->isRunning())
                networkReply->abort();

            currentDownloads.removeAll(networkReply);
            networkReply->deleteLater();
            finishedDownloads.append(reply);
            if (currentDownloads.isEmpty())
                //   all downloads finished
                QCoreApplication::instance()->quit();
        }
    }
}
