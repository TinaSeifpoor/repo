#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reward.h"
#include "questtimer.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qRegisterMetaType<Minion>("Minion");
    qRegisterMetaType<Quest>("Quest");
    ui->setupUi(this);
    ui->wMinionInUseHub->setEnabled(false);
    ui->wQuestProgressHub->setEnabled(false);
    for (int i=0; i<10; ++i)
        ui->wQuestHub->addQuest(Quest());
    ui->wMinionHub->addMinion(Minion());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::questComplete(Minion minion, Quest quest)
{
    if (minion.rewardExperience(Reward(minion,quest).getExperienceReward()))
        ui->wMinionHub->addMinion(Minion());
}

void MainWindow::on_pbGo_clicked()
{
    Minion minion = ui->wMinionHub->getMinion();
    Quest quest = ui->wQuestHub->getQuest();
    ui->wMinionInUseHub->addMinion(minion);
    ui->wQuestProgressHub->addQuest(quest);
    QuestTimer::setQuestTimer(minion, quest, this, SLOT(questComplete(Minion,Quest)));
}
