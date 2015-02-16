#include <QApplication>
#include "mainwindow.h"
#include "ball.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<Ball*>("Ball");

    MainWindow w;
    w.showFullScreen();
    a.processEvents();
    w.initMainWindow();
    return a.exec();
}
