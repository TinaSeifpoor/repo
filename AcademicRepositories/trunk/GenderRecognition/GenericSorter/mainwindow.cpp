#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "visionitem.h"
#include <QSettings>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList argList = qApp->arguments();
    QSettings settings;
    QString OriginalDirPath = settings.value("OriginalDirPath").toString();
    QString LeftDirPath = settings.value("LeftDirPath").toString();
    QString RightDirPath = settings.value("RightDirPath").toString();
    argList.removeFirst();
    if (argList.count()>2) {
        OriginalDirPath = argList.takeFirst();
        LeftDirPath = argList.takeFirst();
        RightDirPath = argList.takeFirst();
    }
    ui->Original->setPath(OriginalDirPath);
    ui->Left->setPath(LeftDirPath);
    ui->Right->setPath(RightDirPath);

    connect(ui->Original, SIGNAL(sendLeftSignal(VisionItem*)), ui->Left, SIGNAL(received(VisionItem*)));
    connect(ui->Right, SIGNAL(sendLeftSignal(VisionItem*)), ui->Left, SIGNAL(received(VisionItem*)));

    connect(ui->Original, SIGNAL(sendRightSignal(VisionItem*)), ui->Right, SIGNAL(received(VisionItem*)));
    connect(ui->Left, SIGNAL(sendRightSignal(VisionItem*)), ui->Right, SIGNAL(received(VisionItem*)));

    connect(ui->Left, SIGNAL(sendLeftSignal(VisionItem*)), ui->Original, SIGNAL(received(VisionItem*)));
    connect(ui->Right, SIGNAL(sendRightSignal(VisionItem*)), ui->Original, SIGNAL(received(VisionItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
