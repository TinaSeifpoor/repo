#include "urlquerymanager.h"
#include <QtNetwork>
URLQueryManager::URLQueryManager()
{
}

void URLQueryManager::query(QUrl url)
{
    QNetworkAccessManager manager;
    QNetworkRequest request(url);
    QNetworkReply *reply(manager.get(request));
    QEventLoop loop;
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();
    emit source(reply->readAll());
}
