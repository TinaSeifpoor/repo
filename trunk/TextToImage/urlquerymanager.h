#ifndef URLQUERYMANAGER_H
#define URLQUERYMANAGER_H
#include <QObject>
#include <QUrl>
class URLQueryManager : public QObject
{
    Q_OBJECT
public:
    URLQueryManager();
public slots:
    void query(QUrl url);
signals:
    void source(QString source);
};

#endif // URLQUERYMANAGER_H
