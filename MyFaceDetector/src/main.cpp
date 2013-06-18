#include <MyFaceDetector.h>
#include <mainwindow.h>
#include <QtGui/QApplication>
#include <QThread>
#include <QMetaType>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QList<EvaluationModel> >("QList<EvaluationModel>");
    qRegisterMetaType<QFileInfoList>("QFileInfoList");
    qRegisterMetaType<QFileInfo>("QFileInfo");
    qRegisterMetaType<cv::Mat>("cv::Mat");

    MainWindow *w = new MainWindow();
    w->show();


    MyFaceDetector* fd = new MyFaceDetector();
    QThread *t = new QThread();
    fd->moveToThread(t);
    t->start();

    QObject::connect(w,     SIGNAL(testForest(QFileInfoList)),                  fd, SLOT(testForest(QFileInfoList)));
    QObject::connect(w,     SIGNAL(loadForest(QFileInfo)),                      fd, SLOT(loadForest(QFileInfo)));
    QObject::connect(fd,    SIGNAL(evaluation(QList<EvaluationModel>)),   w,  SLOT(evaluation(QList<EvaluationModel>)));

    return a.exec();
}
