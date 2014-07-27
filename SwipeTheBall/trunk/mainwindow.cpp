#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ball.h"
#include <QTimer>
#include <QDateTime>
#include <QSignalMapper>
#include <QMouseEvent>
#include <QSettings>
#include "attack.h"

struct Settings {
    int ballVanishMinTime;
    int ballVanishTime;
    int minRadius;
    int radius;
    int minHealth;
    int health;
    int maulDamage;
    int swipeDamage;
    int ballChance;
} gameSettings;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    attack(new Attack())
{
    QSettings settings("settings.ini",QSettings::IniFormat);
    settings.beginGroup("BallVanishSettings");
    gameSettings.ballVanishTime = settings.value("BallVanishTime").toInt();
    gameSettings.ballVanishMinTime = settings.value("BallVanishTimeMin").toInt();
    settings.endGroup();
    settings.beginGroup("RadiusSettings");
    gameSettings.radius = settings.value("Radius").toInt();
    gameSettings.minRadius = settings.value("RadiusMin").toInt();
    settings.endGroup();
    settings.beginGroup("HealthSettings");
    gameSettings.health = settings.value("Health").toInt();
    gameSettings.minHealth = settings.value("HealthMin").toInt();
    settings.endGroup();
    settings.beginGroup("DamageSettings");
    gameSettings.swipeDamage = settings.value("Swipe").toInt();
    gameSettings.maulDamage = settings.value("Maul").toInt();
    settings.endGroup();
    settings.beginGroup("SpawnSettings");
    gameSettings.ballChance = settings.value("BallChance").toInt();
    settings.endGroup();
    qsrand(QDateTime::currentMSecsSinceEpoch());
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    this->fps = new QTimer;
    fps->start(30);
    connect(fps, SIGNAL(timeout()), SIGNAL(frameSignalReceive()));
    connect(this, SIGNAL(frameSignalReceive()), SIGNAL(frameSignalToSend()));
    connect(this, SIGNAL(frameSignalToSend()), SLOT(frame()));
    genBall();
    scene->setSceneRect(0,0,600,600);
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
        Ball* ball = new Ball(ui->graphicsView->scene(), qrand()%gameSettings.ballVanishTime+gameSettings.ballVanishMinTime,
                              qrand()%gameSettings.radius+gameSettings.minRadius, qrand()%gameSettings.health+gameSettings.minHealth,
                              gameSettings.maulDamage, gameSettings.swipeDamage, idx);
        connect(this, SIGNAL(frameSignalToSend()), ball, SLOT(frame()));
        connect(attack, SIGNAL(attackMaul(QRegion)), ball, SLOT(attackMaul(QRegion)));
        connect(attack, SIGNAL(attackSwipe(QLineF)), ball, SLOT(attackSwipe(QLineF)));
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
        //        disconnect(this, SIGNAL(regularHit(QPointF)), ball, SLOT(regularHit(QPointF)));
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
    if (qrand()%10000>gameSettings.ballChance)
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
    attack->press(ui->graphicsView->mapToScene(ui->graphicsView->mapFromParent(ev->pos())),
                  ev->buttons());
}
