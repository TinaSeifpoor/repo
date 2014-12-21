#ifndef URLQUERYMANAGER_H
#define URLQUERYMANAGER_H
#include <QObject>
#include <QUrl>
//#include <QNetworkAccessManager>
#include <QtNetwork>
//class QNetworkReply;
class URLQueryManager : public QObject
{
    Q_OBJECT
public:
    URLQueryManager(QNetworkAccessManager* manager);
public slots:
    void query(QUrl url);
signals:
    void source(QString source);
private slots:
    void sourceReady(QNetworkReply*reply);
private:
    QNetworkAccessManager* manager;
};

#endif // URLQUERYMANAGER_H
