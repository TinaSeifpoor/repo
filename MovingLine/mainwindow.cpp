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
    ballChance(9900)
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
    genBall();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::genBall(int count)
{
    for (int i=0; i<count; ++i) {
        qint16 idx=-1;
        if (!this->availableBalls.isEmpty()) {
            idx = this->availableBalls.takeFirst();
        } else {
            idx = this->balls.count();
        }
        Ball* ball = new Ball(ui->graphicsView->scene(), qrand()%150+75, 20, qrand()%3+1, idx);
        connect(this, SIGNAL(frameSignalToSend()), ball, SLOT(frame()));
        connect(this, SIGNAL(mouseClick(QPointF)), ball, SLOT(mouseClick(QPointF)));
        connect(ball, SIGNAL(hit(qint16)), this, SLOT(hit()), Qt::QueuedConnection);
        connect(ball, SIGNAL(hit(qint16)), this, SLOT(removeBall(qint16)), Qt::QueuedConnection);
        connect(ball, SIGNAL(miss(qint16)), this, SLOT(miss()),Qt::QueuedConnection);
        connect(ball, SIGNAL(miss(qint16)), this, SLOT(removeBall(qint16)), Qt::QueuedConnection);
        if (this->balls.count()>idx) {
            this->balls.replace(idx, ball);
        } else {
            this->balls << ball;
        }
    }
}

void MainWindow::removeBall(qint16 idx)
{
    Ball *ball = balls.at(idx);
    if (ball) {
        disconnect(this, SIGNAL(frameSignalToSend()), ball, SLOT(frame()));
        disconnect(this, SIGNAL(mouseClick(QPointF)), ball, SLOT(mouseClick(QPointF)));
        disconnect(ball, SIGNAL(hit(qint16)), this, SLOT(hit()));
        disconnect(ball, SIGNAL(hit(qint16)), this, SLOT(removeBall(qint16)));
        disconnect(ball, SIGNAL(miss(qint16)), this, SLOT(miss()));
        disconnect(ball, SIGNAL(miss(qint16)), this, SLOT(removeBall(qint16)));
        delete ball;
        this->balls.replace(idx,0);
        this->availableBalls.append(idx);
    }
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
    if (ballChance>1000)
        --ballChance;
    if (qrand()%10000>ballChance)
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
