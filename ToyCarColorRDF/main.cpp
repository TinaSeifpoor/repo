#include "mainwindow.h"
#include <QApplication>
#include "initializer.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    Source* s = Initializer::getSource();

    return a.exec();
}
