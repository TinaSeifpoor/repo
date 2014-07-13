#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "movingline.h"
#include <QTimer>
#include <QDateTime>
#include <QSignalMapper>
#include <QMouseEvent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ballHitMapper(new QSignalMapper(this)),
    ballMissMapper(new QSignalMapper(this)),
    fpsCounter(0)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene;
    scene->setSceneRect(0,0,300,300);
    ui->graphicsView->setScene(scene);

    this->fps = new QTimer;
    fps->start(30);
    connect(fps, SIGNAL(timeout()), SIGNAL(frameSignalReceive()));
    connect(this, SIGNAL(frameSignalReceive()), SIGNAL(frameSignalToSend()));
    connect(this, SIGNAL(frameSignalToSend()), SLOT(frame()));
    connect(ballHitMapper, SIGNAL(mapped(int)), this, SLOT(hit(int)));
    connect(ballMissMapper, SIGNAL(mapped(int)), this, SLOT(miss(int)));
    genBall();
    genBall();
    genBall();
    genBall();
    genBall();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::genBall()
{
    MovingLine* w = new MovingLine(0,ui->graphicsView->scene());
    connect(this, SIGNAL(frameSignalToSend()), w, SLOT(frame()));
    connect(this, SIGNAL(mouseClick(QPointF)), w, SLOT(mouseClick(QPointF)));
    connect(w, SIGNAL(hit()), ballHitMapper, SLOT(map()));
    ballHitMapper->setMapping(w, this->lines.count());
    connect(w, SIGNAL(miss()), ballMissMapper, SLOT(map()));
    ballMissMapper->setMapping(w, this->lines.count());
    this->lines << w;
}

void MainWindow::miss(int idx)
{
    ui->sbScore->setValue(ui->sbScore->value()+ui->sbMiss->value());
    if (lines.at(idx)) {
        delete this->lines.at(idx);
        this->lines.replace(idx,0);
    }
    genBall();
}

void MainWindow::hit(int idx)
{
    ui->sbScore->setValue(ui->sbScore->value()+ui->sbClick->value());
    if (lines.at(idx)) {
        delete this->lines.at(idx);
        this->lines.replace(idx,0);
    }
    genBall();
}

void MainWindow::frame()
{
    if (++fpsCounter%200==0)
        genBall();
    ui->sbScore->setValue(ui->sbScore->value()+ui->sbFrame->value());
}

void MainWindow::on_pushButton_toggled(bool checked)
{
    if (checked) {
        disconnect(this, SIGNAL(frameSignalReceive()), this, SIGNAL(frameSignalToSend()));
    } else {
        connect(this, SIGNAL(frameSignalReceive()), SIGNAL(frameSignalToSend()));
    }
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    emit mouseClick(ui->graphicsView->mapToScene(ui->graphicsView->mapFromParent(ev->pos())));
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    if (QApplication::mouseButtons()&Qt::LeftButton) {
        mousePressEvent(ev);
    }
}
