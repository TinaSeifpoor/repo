#include <QCoreApplication>
#include "downloadmanager.h"
#include "imagesourceparser.h"
#include "urlquerymanager.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString searchString("https://www.google.com/search\?tbm=isch&q=%1");

    QString savePath = "%1/%2";
    if (argc>1)
        savePath = savePath.arg(argv[2]);
    else
        savePath = savePath.arg("./");

    savePath = savePath.arg(argv[1]);
    DownloadManager manager(savePath);
    ImageSourceParser parser(QRegExp("<a href=\"http://www.google.com/imgres\?imgurl="),QRegExp("&amp;imgrefurl="));
    QObject::connect (&parser, SIGNAL(download(QUrl)), &manager, SLOT(doDownload(QUrl)));

    URLQueryManager urlManager;
    QObject::connect (&urlManager, SIGNAL(source(QString)), &parser, SLOT(urlSource(QString)));
    urlManager.query(searchString.arg(argv[1]));



    return a.exec();
}
