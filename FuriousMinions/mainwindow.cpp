#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbGo_clicked()
{
    QList<Minion> minions = ui->wMinionHub->selectedMinions();
    QList<Quest> quests = ui->wQuestHub->selectedQuests();
    qDebug(QString("%1 quests & %2 minions").arg(minions.count()).arg(quests.count()).toLatin1());
}
