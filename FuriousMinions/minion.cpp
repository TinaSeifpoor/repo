#include "minion.h"
#include "affiniteetemplate.h"
#include <QTimer>
#include <QHash>
#include <QPixmap>
#include <QTextDocument>
#include <QPainter>
#include <QFile>
QStringList nameList;
int minionCounter=0;
QHash<MinionRank, Minion> allMinions;
QString fontText(QColor color, int size, QString text) {
    return QString("<p style=\"font-size:%1px;color:%2;text-shadow:1px 1px 1px #000;\">%3</p>").arg(size).arg(color.name()).arg(text);
}

class MinionData : public AffiniteeTemplate
{
    QString __minionName;
    QList<QObject*> objsToNotify;
    QList<const char*> membersToNotify;
    QPixmap* __pixmap;
    void setName() {
        if (nameList.isEmpty()) {
            QFile file(":/names/names.txt");
            if (file.open(QFile::ReadOnly)) {
                while (!file.atEnd())
                    nameList << QString(file.readLine()).remove("\n");
            }
            file.close();
        }
        QStringList affinityTexts;
        foreach (AffinityTypes type, getAffinities()) {
            affinityTexts << fontText(affinityToColor(type),10,coolNumericFormat(getAffinityPower(type)));
        }
        __minionName = nameList.value(get()%nameList.count());
        QTextDocument text;
        text.setHtml(QString("<i>%1</i>&nbsp;&nbsp;&nbsp;%2").arg(fontText(QColor(242,242,242),10,__minionName)).arg(affinityTexts.join("")));
        if (__pixmap)
            delete __pixmap;
        __pixmap = new QPixmap(text.size().width(), text.size().height());
        __pixmap->fill(Qt::transparent);
        QPainter painter(__pixmap);
        text.drawContents(&painter,__pixmap->rect());
    }
    virtual QHash<AffinityTypes, Power> setPowers(QList<AffinityTypes> types) {
        QHash<AffinityTypes, Power> powers;
        foreach (AffinityTypes type, types) {
            powers.insert(type, qrand()%80 + 30);
        }
        return powers;
    }

public:
    MinionData():__pixmap(0){

    }

    virtual void set(int seed)
    {
        AffiniteeTemplate::set(seed);
        setName();
        minionCounter++;
        notify();
    }

    ~MinionData() {
        minionCounter--;
        if (__pixmap)
            delete __pixmap;
    }

    QPixmap* getPixmap() const {return __pixmap;}

    QString minionName() const {return __minionName;}

    void addObj(QObject* obj, const char* member) {
        objsToNotify << obj;
        membersToNotify << member;
    }

    void removeObj(QObject* obj) {
        int i = objsToNotify.indexOf(obj);
        if (i!=-1) {
            objsToNotify.removeAt(i);
            membersToNotify.removeAt(i);
        }
    }

    void notify() const
    {
        for (int i=0; i<objsToNotify.count(); ++i) {
            QTimer::singleShot(0,objsToNotify.value(i), membersToNotify.value(i));
        }
    }
};




Minion::Minion(const Minion &other):__data(other.__data)
{

}

Minion::Minion(int seed):__data(new MinionData())
{
    __data->set(seed);
}

Minion::Minion() : __data(new MinionData())
{
    __data->set(qrand());
}

Minion::~Minion()
{

}

QString Minion::getName() const
{
    return __data->minionName();
}

QPixmap *Minion::getPixmap() const
{
    return __data->getPixmap();
}

QList<AffinityTypes> Minion::getAffinities() const
{
    return __data->getAffinities();
}

Power Minion::getAffinityPower(AffinityTypes affinity) const
{
    return __data->getAffinityPower(affinity);
}

void Minion::setMinionTrigger(QObject *obj, const char *member)
{
    __data->addObj(obj, member);
}

void Minion::removeMinionTrigger(QObject *obj)
{
    __data->removeObj(obj);
}

int Minion::totalNumberOfMinions()
{
    return minionCounter;
}
#include "qmath.h"
GoldCurrency Minion::nextMinionGold()
{
    if (totalNumberOfMinions()==0)
        return 50;
    return qPow(5,totalNumberOfMinions())*totalNumberOfMinions()+50;
}
