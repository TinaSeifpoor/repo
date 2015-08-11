#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("FaceCropper");
    QApplication::setApplicationVersion("0.1");
    QApplication::setOrganizationName("Katiksiz");
    MainWindow w;
    w.show();
    return a.exec();
}
