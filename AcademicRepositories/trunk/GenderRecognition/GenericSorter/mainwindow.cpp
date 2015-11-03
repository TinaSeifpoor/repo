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
    ui->leOriginal->setText(OriginalDirPath);
    this->on_leOriginal_editingFinished();

    ui->leLeft->setText(LeftDirPath);
    this->on_leLeft_editingFinished();

    ui->leRight->setText(RightDirPath);
    this->on_leRight_editingFinished();

    ui->lwOriginal->setBehaviourEnum(ImageResultViewer::BehaviourEnum(ImageResultViewer::RemoveOnSend)|ImageResultViewer::CopyOnReceive);
    ui->lwLeft->setBehaviourEnum(ImageResultViewer::BehaviourEnum(ImageResultViewer::RemoveOnSend)|ImageResultViewer::CopyOnReceive);
    ui->lwRight->setBehaviourEnum(ImageResultViewer::BehaviourEnum(ImageResultViewer::RemoveOnSend)|ImageResultViewer::CopyOnReceive);

    connect(ui->lwOriginal, SIGNAL(sendLeftSignal(VisionItem*)), ui->lwLeft, SLOT(received(VisionItem*)));
    connect(ui->lwRight, SIGNAL(sendLeftSignal(VisionItem*)), ui->lwLeft, SLOT(received(VisionItem*)));

    connect(ui->lwOriginal, SIGNAL(sendRightSignal(VisionItem*)), ui->lwRight, SLOT(received(VisionItem*)));
    connect(ui->lwLeft, SIGNAL(sendRightSignal(VisionItem*)), ui->lwRight, SLOT(received(VisionItem*)));

    connect(ui->lwLeft, SIGNAL(sendLeftSignal(VisionItem*)), ui->lwOriginal, SLOT(received(VisionItem*)));
    connect(ui->lwRight, SIGNAL(sendRightSignal(VisionItem*)), ui->lwOriginal, SLOT(received(VisionItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
#define editFinish(WidgetKey) \
    void MainWindow::on_le ##WidgetKey## _editingFinished() {    \
    QString originalDirPath = ui->le##WidgetKey##->text();\
    QSettings settings; \
    ui->lw##WidgetKey##->setDir(originalDirPath); \
    foreach (QFileInfo info, QDir(originalDirPath).entryInfoList(QDir::Files)) { \
        ui->lw##WidgetKey##->received(new VisionItem(info)); \
    } \
    settings.setValue(#WidgetKey "DirPath",originalDirPath); \
    }

editFinish(Right)
editFinish(Original)
editFinish(Left)
