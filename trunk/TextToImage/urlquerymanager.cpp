#include "urlquerymanager.h"
#include <QtNetwork>
URLQueryManager::URLQueryManager():
    manager(new QNetworkAccessManager)
{
    connect (manager, SIGNAL(finished(QNetworkReply*)), SLOT(sourceReady(QNetworkReply*)));
}

void URLQueryManager::query(QUrl url)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    qDebug(url.toString().toLatin1());
    manager->get(request);
}

void URLQueryManager::sourceReady(QNetworkReply *reply)
{
    emit source(reply->readAll());
}
