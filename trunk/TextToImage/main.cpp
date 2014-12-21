#include <QCoreApplication>
#include "downloadmanager.h"
#include "imagesourceparser.h"
#include "urlquerymanager.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString searchString("http://www.google.com.tr/search?q=%1&biw=1920&bih=955&source=lnms&tbm=isch&sa=X&ei=sTyVVITxEKKY7gbEroHoDg&ved=0CAYQ_AUoAQ&gws_rd=ssl&sout=0");

    QString savePath = "%1/%2";
    if (argc>1)
        savePath = savePath.arg(argv[2]);
    else
        savePath = savePath.arg("./");

    savePath = savePath.arg(argv[1]);
    searchString = searchString.arg(argv[1]);

//    QNetworkAccessManager nam;
    DownloadManager manager(new QNetworkAccessManager, savePath);
    ImageSourceParser parser("imgres?imgurl=","&amp;imgrefurl=");
    QObject::connect (&parser, SIGNAL(download(QUrl)), &manager, SLOT(doDownload(QUrl)));

    URLQueryManager urlManager(new QNetworkAccessManager);
    QObject::connect (&urlManager, SIGNAL(source(QString)), &parser, SLOT(urlSource(QString)));
    urlManager.query(searchString);



    return a.exec();
}
