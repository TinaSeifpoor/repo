#ifndef URLQUERYMANAGER_H
#define URLQUERYMANAGER_H
#include <QObject>
#include <QUrl>
class QNetworkAccessManager;
class QNetworkReply;
class URLQueryManager : public QObject
{
    Q_OBJECT
public:
    URLQueryManager();
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
