#include "urlquerymanager.h"
#include <QtNetwork>
URLQueryManager::URLQueryManager(QNetworkAccessManager* manager):manager(manager)
{
    connect (manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(sourceReady(QNetworkReply*)));
}

void URLQueryManager::query(QUrl url)
{
    QNetworkRequest request(url);
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.3; rv:36.0) Gecko/20100101 Firefox/36.0");
    QNetworkReply* reply = manager->get(request);
    if (reply->isRunning())
        qDebug(url.toString().toLatin1());
}

void URLQueryManager::sourceReady(QNetworkReply *reply)
{
    QUrl redirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    if (!redirectUrl.isEmpty()) {
        query(redirectUrl);
        return;
    }
    emit source(reply->readAll());
}
