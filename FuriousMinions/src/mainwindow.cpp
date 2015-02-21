#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reward.h"
#include "minionselectionwidget.h"
#include "questselectionwidget.h"
#include "globalvariables.h"
#include "synchronizedtimer.h"
#include <QStandardPaths>
#include <QFile>
#include <QDateTime>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand(QDateTime::currentMSecsSinceEpoch());
    qRegisterMetaType<Minion>("Minion");
    qRegisterMetaType<Quest>("Quest");
    ui->setupUi(this);
    GlobalVariables::setGoldLabel(ui->lblGold);
    connect(ui->wQuestProgressHub, SIGNAL(questComplete(Minion)), ui->wMinionHub, SLOT(addMinion(Minion)), Qt::QueuedConnection);
    bool isReset = QApplication::arguments().contains("Reset");
    if (isReset)
        if (loadProgress()) {
            return;
        }
    connect(SynchronizedTimer::getInstance(), SIGNAL(bigEpoch()), SLOT(saveProgress()));
    GlobalVariables::addGold(100);
    for (int i=0; i<5; ++i)
        ui->wQuestHub->addQuest(Quest());

}

MainWindow::~MainWindow()
{
    saveProgress();
    delete ui;
}

void MainWindow::showGuidance(QString title, QString text)
{

}

bool MainWindow::loadProgress()
{
    QString filepath(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)+"/FuriousMinions.dat");
    QFile file(filepath);
    if (file.open(QFile::ReadOnly)) {
        QByteArray progress = QByteArray::fromBase64(QByteArray::fromHex(file.readAll()));
        file.close();
        QDataStream s(&progress, QIODevice::ReadOnly);
        QVariantHash progressHash;
        s >> progressHash;
        if (progressHash.value("Version",0).toDouble()>0.005) {
            GlobalVariables::fromHash(progressHash.value("GlobalVariables").toHash());
            ui->wMinionHub->fromHash(progressHash.value("MinionHub").toHash());
            ui->wQuestHub->fromHash(progressHash.value("QuestHub").toHash());
            ui->wQuestProgressHub->fromHash(progressHash.value("QuestProgressHub").toHash());
            connect(SynchronizedTimer::getInstance(), SIGNAL(bigEpoch()), SLOT(saveProgress()));
            return true;
        }
    }
    return false;
}

void MainWindow::saveProgress()
{
    QVariantHash progressHash;
    progressHash.insert("Version", 0.01);
    progressHash.insert("MinionHub",ui->wMinionHub->toHash());
    progressHash.insert("QuestHub" ,ui->wQuestHub->toHash());
    progressHash.insert("QuestProgressHub", ui->wQuestProgressHub->toHash());
    progressHash.insert("GlobalVariables", GlobalVariables::toHash());
    QByteArray progressByteArray;
    {
        QDataStream s(&progressByteArray, QIODevice::WriteOnly);
        s << progressHash;
    }
    QString filepath(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)+"/FuriousMinions.dat");
    QFile file(filepath);
    if (file.open(QFile::WriteOnly)) {
        file.write(progressByteArray.toBase64().toHex());
        file.close();
    }
}

void MainWindow::on_pbGo_clicked()
{
    MinionSelectionWidget* msw = ui->wMinionHub->getMinionSelectionWidget();
    if (!msw) {
        showGuidance("Select a minion", "You should select a minion!");
        return;
    }
    QuestSelectionWidget* qsw  = ui->wQuestHub->getQuestSelectionWidget();
    if (!qsw) {
        showGuidance("Select a quest", "You should select a quest!");
        return;
    }
    qsw->deleteLater();
    msw->deleteLater();
    ui->wQuestHub->addQuest(Quest());
    ui->wQuestProgressHub->startQuest(msw->getMinion(), qsw->getQuest());
}
