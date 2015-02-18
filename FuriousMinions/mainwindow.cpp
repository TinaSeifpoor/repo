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
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::questComplete(Minion minion, Quest quest)
//{
//    if (minion.rewardExperience(Reward(minion,quest).getExperienceReward()))
//        ui->wMinionHub->addMinion(Minion());
//}

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
    ui->wQuestProgressHub->startQuest(msw->getMinion(), qsw->getQuest());
}
