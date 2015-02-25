#include "mainwindow.h"
#include <QApplication>
#include <perktemplate.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    Perks::PerkTemplate c;
//    c.addRank(Perks::AmountForMoreQuestReward);
//    c.addRank(Perks::AmountForMoreQuestReward);
//    c.addRank(Perks::ChanceForInstantQuest);
//    c.addRank(Perks::ChanceForInstantQuest);
//    c.addRank(Perks::MinionGoldGainFactor);
//    c.addRank(Perks::MinionGoldGainFactor);
//    c+c;
//    qDebug(QString::number(c.rank(Perks::MinionGoldGainFactor)).toLatin1());
    return a.exec();
}
