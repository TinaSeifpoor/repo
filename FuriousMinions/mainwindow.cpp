#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reward.h"
#include "minionselectionwidget.h"
#include "questselectionwidget.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qRegisterMetaType<Minion>("Minion");
    qRegisterMetaType<Quest>("Quest");
    ui->setupUi(this);
    for (int i=0; i<10; ++i)
        ui->wQuestHub->addQuest(Quest());
    ui->wMinionHub->addMinion(Minion());
    ui->wMinionHub->addMinion(Minion());
    ui->wMinionHub->addMinion(Minion());
    ui->wMinionHub->addMinion(Minion());
    ui->wMinionHub->addMinion(Minion());
    ui->wMinionHub->addMinion(Minion());
    ui->wMinionHub->addMinion(Minion());
    ui->wMinionHub->addMinion(Minion());
    connect(ui->wQuestProgressHub, SIGNAL(questComplete(Reward)), SLOT(questComplete(Reward)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::questComplete(Reward reward)
{
    Minion minion = reward.getMinion();
    if (minion.rewardExperience(reward.getReward())) {
        ui->wMinionHub->addMinion(Minion());
    }
    ui->wMinionHub->addMinion(minion);
}

void MainWindow::showGuidance(QString title, QString text)
{

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
