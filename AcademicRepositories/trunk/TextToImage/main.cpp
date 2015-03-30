#include <QCoreApplication>
#include "downloadmanager.h"
#include "imagesourceparser.h"
#include "urlquerymanager.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString searchString("http://www.google.com.tr/search?q=%1&biw=1920&bih=955&source=lnms&tbm=isch&sa=X&ei=sTyVVITxEKKY7gbEroHoDg&ved=0CAYQ_AUoAQ&gws_rd=ssl&sout=0");

    QString savePath;
    if (argc>1)
        savePath = argv[2];
    else
        savePath = "./";

    QString query = argv[1];
    query.replace(" ", "+");
    query.append("\"");
    query.prepend("\"");

    searchString = searchString.arg(query);

    DownloadManager manager(new QNetworkAccessManager, savePath);
    ImageSourceParser parser("imgres?imgurl=","&amp;imgrefurl=");
    QObject::connect (&parser, SIGNAL(download(QUrl)), &manager, SLOT(doDownload(QUrl)));

    URLQueryManager urlManager(new QNetworkAccessManager);
    QObject::connect (&urlManager, SIGNAL(source(QString)), &parser, SLOT(urlSource(QString)));
    urlManager.query(searchString);



    return a.exec();
}
