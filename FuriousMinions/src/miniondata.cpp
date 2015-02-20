#include "miniondata.h"
#include <QTimer>
#include <QHash>
#include <QPixmap>
#include <QTextDocument>
#include <QPainter>
#include <QFile>
#include "qmath.h"
QStringList nameList;
QHash<Rank, int> minionCounterHash;
int minionCounter=0;




QString fontText(QColor color, int size, QString text) {
    return QString("<p style=\"font-size:%1px;color:%2;text-shadow:1px 1px 1px #000;\">%3</p>").arg(size).arg(color.name()).arg(text);
}

void MinionData::setName() {
    if (nameList.isEmpty()) {
        QFile file(":/names/names.txt");
        if (file.open(QFile::ReadOnly)) {
            while (!file.atEnd())
                nameList << QString(file.readLine()).remove("\n");
        }
        file.close();
    }
    __minionName = nameList.value(get()%nameList.count());
    for (int i=0; i<__rank-1;++i)
        __minionName.append('+');
}

QHash<AffinityTypes, Power> MinionData::setPowers(QList<AffinityTypes> types) {
    QHash<AffinityTypes, Power> powers;
    foreach (AffinityTypes type, types) {
        Power power = qrand()%80 + 30;
        Power ascendingPower = qPow(power,this->__rank);
        if (ascendingPower<0)
            qDebug(QString("Negative value from: %1, %2, %3").arg(power).arg(__rank).arg(ascendingPower).toLatin1());

        powers.insert(type, ascendingPower);
    }
    return powers;
}

MinionData::MinionData(){}

MinionData::~MinionData() {
    minionCounterHash[__rank]--;
    minionCounter--;
}

Rank MinionData::getRank() const {return __rank;}
QString MinionData::getMinionResourceIcon() const {
    return ":/icons/minions/35/minion1.gif";
}

void MinionData::set(int seed)
{
    __rank = nextRank();
    AffiniteeTemplate::set(seed);
    setName();
    minionCounterHash[__rank]++;
    minionCounter++;
    notify();
}


QString MinionData::minionName() const {
    return __minionName;
}

void MinionData::addObj(QObject *obj, const char *member) {
    objsToNotify << obj;
    membersToNotify << member;
}

void MinionData::removeObj(QObject *obj) {
    int i = objsToNotify.indexOf(obj);
    if (i!=-1) {
        objsToNotify.removeAt(i);
        membersToNotify.removeAt(i);
    }
}

void MinionData::notify() const
{
    for (int i=0; i<objsToNotify.count(); ++i) {
        QTimer::singleShot(0,objsToNotify.value(i), membersToNotify.value(i));
    }
}

int MinionData::minionCount(Rank rank)
{
    return minionCounterHash.value(rank);
}

int MinionData::minionCount()
{
    return minionCounter;
}

GoldCurrency MinionData::nextMinionGold()
{
    if (minionCount()==0)
        return 50;
    return qPow(5,minionCount())*minionCount()+50;
}

Rank MinionData::nextRank()
{
    return calculateNextRank(minionCounterHash, 5);
}
