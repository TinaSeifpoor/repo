//#include "mainwindow.h"
#include <QApplication>
#include "cscamerafolder.h"
#include "imagewidget.h"
#include <QGraphicsView>
int getRand() {return qrand()%250;}
QRect getRandomRect() {
    return QRect(getRand(),getRand(),getRand(),getRand());
}

void makePair (CSCamera* c) {
    ImageWidget*    iw= new ImageWidget();
    iw->connect(c, SIGNAL(updated(CSImage)), SLOT(setImage(CSImage)));
    QGraphicsView* v = new QGraphicsView();
    v->setScene(iw);
    v->show();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    for (int i=1; i<argc; ++i) {
        CSCameraFolder* f = new CSCameraFolder(argv[i]);
        makePair(f);
        for (int j=0; j<qrand()%5 +1; ++j) {
            makePair(new CSCamera(f, getRandomRect()));
        }
    }
    return a.exec();
}

