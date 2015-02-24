#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "movingline.h"
#include <QTimer>
#include <QDateTime>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene;
    scene->setSceneRect(0,0,300,300);
    w = new MovingLine(0,scene);
    ui->graphicsView->setScene(scene);
    this->fps = new QTimer;
    fps->start(30);
    connect(fps, SIGNAL(timeout()), w, SLOT(frame()));
    connect(fps, SIGNAL(timeout()), SLOT(frame()));
    connect(w, SIGNAL(hit()), SLOT(hit()));
    connect(w, SIGNAL(miss()), SLOT(miss()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::miss()
{
    ui->sbScore->setValue(ui->sbScore->value()+ui->sbMiss->value());
}

void MainWindow::hit()
{
    ui->sbScore->setValue(ui->sbScore->value()+ui->sbClick->value());
}

void MainWindow::frame()
{
    ui->sbScore->setValue(ui->sbScore->value()+ui->sbFrame->value());
}

void MainWindow::on_pushButton_toggled(bool checked)
{
    if (checked) {
        disconnect(fps, SIGNAL(timeout()), w, SLOT(frame()));
        disconnect(fps, SIGNAL(timeout()), this,SLOT(frame()));
    } else {
        connect(fps, SIGNAL(timeout()), w, SLOT(frame()));
        connect(fps, SIGNAL(timeout()), SLOT(frame()));
    }
}
