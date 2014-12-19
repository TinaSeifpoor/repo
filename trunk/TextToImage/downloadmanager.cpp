#include "downloadmanager.h"

DownloadManager::DownloadManager(QString downloadPath):_downloadDir(downloadPath)
{
    connect(&manager, SIGNAL(finished(QNetworkReply*)),
            SLOT(downloadFinished(QNetworkReply*)));
}

void DownloadManager::doDownload(const QUrl &url)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);

    currentDownloads.append(reply);
}

QString DownloadManager::saveFileName(const QUrl &url)
{
    QString path = _downloadDir.filePath(url.path());
    _downloadDir.mkpath(path);
    QString basename = QFileInfo(path).fileName();


    if (basename.isEmpty())
        basename = "download";

    if (QFile::exists(basename)) {
        // already exists, don't overwrite
        int i = 0;
        basename += '.';
        while (QFile::exists(basename + QString::number(i)))
            ++i;

        basename += QString::number(i);
    }
    return _downloadDir.filePath(basename);
}

bool DownloadManager::saveToDisk(const QString &filename, QIODevice *data)
{
//    QFileInfo fileInfo(filename);
//    if (fileInfo.exists())
//        saveToDisk(QString("%1/%2-%3.%4").arg(fileInfo.path()).arg(fileInfo.fileName()).arg("a").arg(fileInfo.completeSuffix()),data);
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

//void DownloadManager::execute()
//{
//    QStringList args = QCoreApplication::instance()->arguments();
//    args[0]="http://www.google.ru/images/srpr/logo3w.png";

//    QString arg=args[0];

//    QUrl url = QUrl::fromEncoded(arg.toLocal8Bit());
//    doDownload(url);
//}

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

    if (currentDownloads.isEmpty())
        //   all downloads finished
        QCoreApplication::instance()->quit();
}
