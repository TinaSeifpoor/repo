#include "mainwindow.h"
#include <QApplication>
#include "perktemplate.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    Perks::PerkTemplate c;
    int level = 0;
    while (level < 9999)
    {
        ++level;
        qDebug(QString::number(c.rank(Perks::AmountForMoreQuestReward)).toLatin1());
        if (c.minionChanceForPerk())
            c.addRank(Perks::AmountForMoreQuestReward);
    }
    qDebug(QString::number(c.rank(Perks::AmountForMoreQuestReward)).toLatin1());
    qDebug(QString::number(level).toLatin1());
//    return a.exec();
}
