#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ball.h"
#include <QTimer>
#include <QDateTime>
#include <QMouseEvent>
#include <QSettings>
#include <QGestureEvent>
#include "attack.h"
#include "animationfactory.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QSettings settings("settings.ini",QSettings::IniFormat);
    if (settings.allKeys().isEmpty()) {
        settings.beginGroup("BallVanishSettings");
        settings.setValue("BallVanishTime",150);
        settings.setValue("BallVanishTimeMin",250);
        settings.endGroup();
        settings.beginGroup("HealthSettings");
        settings.setValue("Health",10);
        settings.setValue("HealthMin",1);
        settings.endGroup();
        settings.beginGroup("DamageSettings");
        settings.setValue("Swipe",1);
        settings.setValue("Maul",4);
        settings.endGroup();
        settings.beginGroup("RadiusSettings");
        settings.setValue("SwipeShort",80);
        settings.setValue("SwipeLong",320);
        settings.setValue("MaulRadius",120);
        settings.endGroup();
        settings.beginGroup("SpawnSettings");
        settings.setValue("BallChance",9900);
        settings.endGroup();
        settings.beginGroup("WindowSettings");
        settings.setValue("Width",713);
        settings.setValue("Height",1219);
        settings.endGroup();
    }
    settings.beginGroup("BallVanishSettings");
    gameSettings.ballVanishTime = settings.value("BallVanishTime").toInt();
    gameSettings.ballVanishMinTime = settings.value("BallVanishTimeMin").toInt();
    settings.endGroup();
    settings.beginGroup("HealthSettings");
    gameSettings.health = settings.value("Health").toInt();
    gameSettings.minHealth = settings.value("HealthMin").toInt();
    settings.endGroup();
    settings.beginGroup("DamageSettings");
    gameSettings.swipeDamage = settings.value("Swipe").toInt();
    gameSettings.maulDamage = settings.value("Maul").toInt();
    settings.endGroup();
    settings.beginGroup("RadiusSettings");
    gameSettings.swipeLength2 = settings.value("SwipeShort").toDouble();
    gameSettings.swipeLength1 = settings.value("SwipeLong").toDouble();
    gameSettings.maulRadius = settings.value("MaulRadius").toDouble();
    settings.endGroup();
    settings.beginGroup("SpawnSettings");
    gameSettings.ballChance = settings.value("BallChance").toInt();
    settings.endGroup();
    settings.beginGroup("WindowSettings");
    gameSettings.width = settings.value("Width").toInt();
    gameSettings.height = settings.value("Height").toInt();
    settings.endGroup();
    qsrand(QDateTime::currentMSecsSinceEpoch());


    ui->setupUi(this);
}

void MainWindow::initMainWindow()
{
    gameSettings.width = this->width() ;
    gameSettings.height = this->height();
    grabMouse();
//    grabGesture(Qt::SwipeGesture);
    QGraphicsScene* scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    ui->graphicsView->installEventFilter(this);
    scene->installEventFilter(this);
    attack= new Attack(gameSettings.maulRadius, gameSettings.swipeLength1, gameSettings.swipeLength2);
    animationFactory = new AnimationFactory(scene);
    connect(attack, SIGNAL(attackMaul(QRegion)), animationFactory, SLOT(maul(QRegion)));
    connect(attack, SIGNAL(attackSwipe(QLineF)), animationFactory, SLOT(swipe(QLineF)));

    this->fps = new QTimer;
    fps->start(20);
    connect(fps, SIGNAL(timeout()), SIGNAL(frameSignalReceive()));
    connect(this, SIGNAL(frameSignalReceive()), SIGNAL(frameSignalToSend()));
    connect(this, SIGNAL(frameSignalToSend()), SLOT(frame()));
    connect(this, SIGNAL(frameSignalToSend()), animationFactory, SIGNAL(frame()));
    genBall();
    QRect screenRect = this->rect();
    screenRect-=QMargins(5,5,5,5);
    scene->setSceneRect(screenRect);
    ui->graphicsView->setGeometry(this->rect());
    QPixmap pim(":/images/BG");
    scene->setBackgroundBrush(pim.scaled(screenRect.width(), screenRect.height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    this->score = scene->addText("0",QFont("Helvetica [Cronyx]", 16));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::genBall(int count)
{
    for (int i=0; i<count; ++i) {
        Ball* ball = new Ball(ui->graphicsView->scene(), qrand()%gameSettings.ballVanishTime+gameSettings.ballVanishMinTime,
                              qrand()%gameSettings.health+gameSettings.minHealth, gameSettings.maulDamage, gameSettings.swipeDamage);
        this->newBall(ball);
    }
}

void MainWindow::removeBall(double,qint16 idx)
{
    Ball *ball = balls.at(idx);
    if (ball) {
        disconnect(this, SIGNAL(frameSignalToSend()), ball, SLOT(frame()));
        disconnect(ball, SIGNAL(hit(double, qint16)), this, SLOT(hit(double)));
        disconnect(ball, SIGNAL(hit(double, qint16)), this, SLOT(removeBall(double, qint16)));
        disconnect(ball, SIGNAL(miss(double, qint16)), this, SLOT(miss(double)));
        disconnect(ball, SIGNAL(miss(double, qint16)), this, SLOT(removeBall(double,qint16)));
        disconnect(ball, SIGNAL(newBall(Ball*)), this, SLOT(newBall(Ball*)));
        ball->deleteLater();
        this->balls.replace(idx,0);
        this->availableBalls.append(idx);
    }
}

void MainWindow::miss(double health)
{
    this->score->setPlainText(QString::number(this->score->toPlainText().toInt()-health*5000));
//    ui->sbScore->setValue(ui->sbScore->value()-health*5000);
}

void MainWindow::hit(double health)
{
    this->score->setPlainText(QString::number(this->score->toPlainText().toInt()+health*600));
//    ui->sbScore->setValue(ui->sbScore->value()+600*health);
}

void MainWindow::frame()
{
    if (qrand()%10000>gameSettings.ballChance)
        genBall();
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
    attack->press(ui->graphicsView->mapToScene(ui->graphicsView->mapFromParent(ev->pos())),
                  ev->buttons());
}

void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    attack->release(ui->graphicsView->mapToScene(ui->graphicsView->mapFromParent(ev->pos())));
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
    connect(attack, SIGNAL(attackMaul(QRegion)), ball, SLOT(attackMaul(QRegion)));
    connect(attack, SIGNAL(attackSwipe(QLineF)), ball, SLOT(attackSwipe(QLineF)));
    connect(ball, SIGNAL(hit(double,qint16)), this, SLOT(hit(double)), Qt::QueuedConnection);
    connect(ball, SIGNAL(hit(double,qint16)), this, SLOT(removeBall(double,qint16)), Qt::QueuedConnection);
    connect(ball, SIGNAL(miss(double,qint16)), this, SLOT(miss(double)),Qt::QueuedConnection);
    connect(ball, SIGNAL(miss(double,qint16)), this, SLOT(removeBall(double,qint16)), Qt::QueuedConnection);
    connect(ball, SIGNAL(newBall(Ball*)), this, SLOT(newBall(Ball*)), Qt::QueuedConnection);
    if (this->balls.count()>idx) {
        this->balls.replace(idx, ball);
    } else {
        this->balls << ball;
    }

}
