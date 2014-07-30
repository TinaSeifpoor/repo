#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ball.h"
#include <QTimer>
#include <QDateTime>
#include <QMouseEvent>
#include <QSettings>
#include <QRect>
#include "attack.h"
#include "animationfactory.h"
#include "scoreboard.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    init(false),
    isPaused(false),
    resetGameAtResume(false)
{
    QSettings settings("settings.ini",QSettings::IniFormat);
    if (settings.allKeys().isEmpty()) {
        settings.beginGroup("SizeSettings");
        settings.setValue("Radius",80);
        settings.setValue("RadiusMin",80);
        settings.setValue("MaulRadius",60);
        settings.endGroup();
    }
    settings.beginGroup("SizeSettings");
    gameSettings.radius = settings.value("Radius").toInt();
    gameSettings.minRadius = settings.value("RadiusMin").toInt();
    gameSettings.maulRadius = settings.value("MaulRadius").toDouble();
    settings.endGroup();
    qsrand(QDateTime::currentMSecsSinceEpoch());
    ui->setupUi(this);
}

void MainWindow::initMainWindow()
{
    init = true;
    grabMouse();
    //    grabGesture(Qt::SwipeGesture);
    QGraphicsScene* scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    ui->graphicsView->installEventFilter(this);
    scene->installEventFilter(this);
    attack= new Attack(gameSettings.maulRadius);
    animationFactory = new AnimationFactory(scene);
    connect(attack, SIGNAL(attackMaul(QRegion)), animationFactory, SLOT(maul(QRegion)));

    this->fps = new QTimer;
    fps->start(20);
    connect(fps, SIGNAL(timeout()), SIGNAL(frameSignalReceive()));
    connect(this, SIGNAL(frameSignalReceive()), SIGNAL(frameSignalToSend()));
    connect(this, SIGNAL(frameSignalToSend()), SLOT(frame()));
    connect(this, SIGNAL(frameSignalToSend()), animationFactory, SIGNAL(frame()));
    genBall();
    this->score = new ScoreBoard(scene);
    resizeEvent(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::genBall(int count)
{
    for (int i=0; i<count; ++i) {
        Ball* ball = new Ball(ui->graphicsView->scene(), qrand()%gameSettings.radius+gameSettings.minRadius);
        this->newBall(ball);
    }
}

void MainWindow::removeBall(double,qint16 idx)
{
    Ball *ball = balls.at(idx);
    if (ball) {
        disconnect(this, SIGNAL(frameSignalToSend()), ball, SLOT(frame()));
        disconnect(ball, SIGNAL(hit(double, qint16)), this, SLOT(hit(double)));
        disconnect(attack, SIGNAL(attackMaul(QRegion)), ball, SLOT(touch(QRegion)));
        disconnect(ball, SIGNAL(hit(double, qint16)), this, SLOT(removeBall(double, qint16)));
        disconnect(ball, SIGNAL(miss(double, qint16)), this, SLOT(miss()));
        disconnect(ball, SIGNAL(miss(double, qint16)), this, SLOT(removeBall(double,qint16)));
        disconnect(ball, SIGNAL(newBall(Ball*)), this, SLOT(newBall(Ball*)));
        ball->deleteLater();
        this->balls.replace(idx,0);
        this->availableBalls.append(idx);
    }
}

void MainWindow::miss()
{
    pause();
    resetGameAtResume=true;
}

void MainWindow::hit(double health)
{
    this->score->addScore(health*600);
    genBall();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    QPointF pos = ui->graphicsView->mapToScene(ui->graphicsView->mapFromParent(ev->pos()));
    if (score->boundingRect().contains(pos)) {
        if (!isPaused)
            this->pause();
        else
            this->resume();
    } else {
        attack->release(pos);
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *ev)
{
    if (ev->type()==QEvent::WindowDeactivate) {
        this->pause();
    } else if (ev->type()== QEvent::WindowActivate) {
//        this->resume();
    }
    return QMainWindow::eventFilter(obj,ev);
}

void MainWindow::pause()
{
    if (!isPaused)
        disconnect(this, SIGNAL(frameSignalReceive()), this, SIGNAL(frameSignalToSend()));
    this->isPaused=true;
}

void MainWindow::resume()
{
    if (isPaused)
        connect(this, SIGNAL(frameSignalReceive()), SIGNAL(frameSignalToSend()));
    if (resetGameAtResume) {
        resetGameAtResume=false;
        score->reset();
        genBall();
    }

    this->isPaused=false;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    if (init) {
        QRect screenRect = this->rect();
        screenRect-=QMargins(5,5,5,5);
        ui->graphicsView->scene()->setSceneRect(screenRect);

        ui->graphicsView->setGeometry(this->rect());
            QPixmap pim(":/images/BG");
        ui->graphicsView->scene()->setBackgroundBrush(pim.scaled(ui->graphicsView->scene()->sceneRect().width(), ui->graphicsView->scene()->sceneRect().height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        score->addScore(0);
    }
}

void MainWindow::newBall(Ball *ball)
{
    qint16 idx=-1;
    if (!this->availableBalls.isEmpty()) {
        idx = this->availableBalls.takeFirst();
    } else {
        idx = this->balls.count();
    }
    ball->setIndex(idx);

    connect(this, SIGNAL(frameSignalToSend()), ball, SLOT(frame()));
    connect(attack, SIGNAL(attackMaul(QRegion)), ball, SLOT(touch(QRegion)));
    connect(ball, SIGNAL(hit(double,qint16)), this, SLOT(hit(double)), Qt::QueuedConnection);
    connect(ball, SIGNAL(hit(double,qint16)), this, SLOT(removeBall(double,qint16)), Qt::QueuedConnection);
    connect(ball, SIGNAL(miss(double,qint16)), this, SLOT(miss()),Qt::QueuedConnection);
    connect(ball, SIGNAL(miss(double,qint16)), this, SLOT(removeBall(double,qint16)), Qt::QueuedConnection);
    connect(ball, SIGNAL(newBall(Ball*)), this, SLOT(newBall(Ball*)), Qt::QueuedConnection);
    if (this->balls.count()>idx) {
        this->balls.replace(idx, ball);
    } else {
        this->balls << ball;
    }

}
