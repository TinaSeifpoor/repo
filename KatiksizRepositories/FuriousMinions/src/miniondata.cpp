#include "miniondata.h"
#include <QTimer>
#include <QHash>
#include <QPixmap>
#include <QTextDocument>
#include <QPainter>
#include <QFile>
#include "qmath.h"
#include "globalvariables.h"
QStringList nameList;





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
}

void MinionData::setPowers(QList<AffinityTypes> types) {
    __affinityPowers.clear();
    foreach (AffinityTypes type, types) {
        Power power = qrand()%80 + 30;
        Power ascendingPower = qPow(power,this->__rank);
        __affinityPowers.insert(type, ascendingPower);
    }
}

MinionData::MinionData(){}

MinionData::~MinionData() {
}

Rank MinionData::getRank() const {return __rank;}

QVariantHash MinionData::toHash() const
{
        QVariantHash minionHash;
        minionHash.insert("Rank", __rank);
        minionHash.insert("Seed", get());
        minionHash.insert("Icon", getMinionResourceIcon());
        minionHash.insert("Name", minionName());
        minionHash.insert("nQuests", __nQuestsCompleted);
        QVariantHash powersHash;
        foreach (AffinityTypes type, getAffinities()) {
            powersHash.insert(affinityString(type), getAffinityPower(type));
        }
        minionHash.insert("Powers", powersHash);
        return minionHash;
}

MinionData *MinionData::fromHash(QVariantHash hash)
{
    MinionData* md = new MinionData();
    md->set(hash.value("Seed", qrand()).toInt(),true);
    md->__rank = hash.value("Rank",1).toInt();
    md->__icon = hash.value("Icon",md->__icon).toString();
    md->__minionName = hash.value("Name", md->__minionName).toString();
    md->__nQuestsCompleted = hash.value("nQuests",0).toInt();
    md->__affinityPowers.clear();
    QVariantHash powersHash = hash.value("Powers").toHash();
    foreach (QString affinityStr, powersHash.keys())
        md->__affinityPowers.insert(affinityFromString(affinityStr),powersHash.value(affinityStr).toDouble());
    return md;
}
QString MinionData::getMinionResourceIcon() const {
    return __icon;
}

void MinionData::set(int seed, bool isHidden)
{
    __rank = 1;
    AffiniteeTemplate::set(seed);
    setName();
    if (__affinityPowers.keys().contains(Earth))
        __icon = ":/icons/minions/35/resources/35x35/minionearth1.gif";
    else if(__affinityPowers.keys().contains(Air))
        __icon = ":/icons/minions/35/resources/35x35/minionair1.gif";
    else if(__affinityPowers.keys().contains(Fire))
        __icon = ":/icons/minions/35/resources/35x35/minionfire1.gif";
    else if(__affinityPowers.keys().contains(Water))
        __icon = ":/icons/minions/35/resources/35x35/minionwater1.gif";
    else if(__affinityPowers.keys().contains(Death))
        __icon = ":/icons/minions/35/resources/35x35/miniondeath1.gif";
    else //nature
        __icon = ":/icons/minions/35/resources/35x35/minionnature1.gif";
    if (!isHidden)
        GlobalVariables::addMinion(__rank);
    __nQuestsCompleted=0;
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

void MinionData::questCompleted()
{
    ++__nQuestsCompleted;
    if (GlobalVariables::calculateMinionRank(getRank(),__nQuestsCompleted)) {
        ++__rank;
        __minionName.append('+');
        setPowers(getAffinities());
    }


}

