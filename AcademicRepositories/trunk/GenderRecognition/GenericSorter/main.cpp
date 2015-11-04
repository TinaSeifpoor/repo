#include "mainwindow.h"
#include <QApplication>
#include <QMetaType>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName("GenericSorter");
    QApplication::setOrganizationDomain("www.cihansari.com");
    QApplication::setOrganizationName("cihansari");
    MainWindow w;
    w.show();

    return a.exec();
}
