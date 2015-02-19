#include "quest.h"
#include "affiniteetemplate.h"
#include "qmath.h"
#include <QTimer>
#include <QTime>
#include <QPixmap>
#include <QTextDocument>
#include <QPainter>
class QuestData : public AffiniteeTemplate
{
protected:
    QList<QObject*> objsToNotify;
    QList<const char*> membersToNotify;
    int __questTime;
    QPixmap __pixmap;
    QTextDocument* __textDocument;
    QString __textDescription;
    void notify() const
    {
        for (int i=0; i<objsToNotify.count(); ++i) {
            QTimer::singleShot(0,objsToNotify.value(i), membersToNotify.value(i));
        }
    }
    virtual QHash<AffinityTypes, Power> setPowers(QList<AffinityTypes> types) {
        QHash<AffinityTypes, Power> powers;
        foreach (AffinityTypes type, types) {
            powers.insert(type, qrand()%600 + 800);
        }
        return powers;
    }

    int genTime() const
    {
        int nAffinities = getAffinities().count();
        int totalPower=0;
        foreach (AffinityTypes type, getAffinities())
            totalPower+=getAffinityPower(type);
        nAffinities*=2.5;
        int time = 86*totalPower/nAffinities;
        return time;
    }
public:
    QuestData():__pixmap(QPixmap(1,1)),__textDocument(new QTextDocument()) {}
    virtual void set(int seed)
    {
        __textDescription = "Garden";
        AffiniteeTemplate::set(seed);
        __questTime = this->genTime();
        notify();
    }
    ~QuestData() {
//        delete __pixmap;
        delete __textDocument;
    }

    int time() const {return __questTime;}
    void setTime(int time) {
        __questTime = time;
        notify();
    }
    QPixmap getPixmap() {
        QStringList affinityTexts;
        foreach (AffinityTypes type, getAffinities()) {
            affinityTexts << QString("<font color=%1 size=\"4\">%2</font>").arg(affinityToColor(type).name()).arg(coolNumericFormat(getAffinityPower(type)));
        }
        QString timeText = QString("Time: %1").arg(QTime().addMSecs(time()).toString());
        __textDocument->setHtml(QString("<i><font color=%1 size=\"6\">%2</font></i>&nbsp;&nbsp;&nbsp;(%3)<br>%4").arg("white",__textDescription,affinityTexts.join("&#09;"),
                     QString("<i><font color=%1 size=\"6\">%2</font></i>").arg("white",timeText)));
        __pixmap = __pixmap.scaled(__textDocument->size().width(), __textDocument->size().height());
        __pixmap.fill(Qt::transparent);
        QPainter painter(&__pixmap);
        __textDocument->drawContents(&painter,__pixmap.rect());
        __pixmap.toImage().save("d:/test.jpg");
        return __pixmap;
    }
    void addObj(QObject* obj, const char* member) {
        objsToNotify << obj;
        membersToNotify << member;
    }
};

Quest::Quest(const Quest &other) : __data(other.__data)
{

}

Quest::Quest(int seed) : __data(new QuestData())
{
    __data->set(seed);
}

Quest::~Quest()
{

}

Quest::Quest():__data(new QuestData()){
    __data->set(qrand());
}

int Quest::getTime() const
{
    return __data->time();
}

Power Quest::getAffinityPower(AffinityTypes type) const
{
    return __data->getAffinityPower(type);
}

QList<AffinityTypes> Quest::getAffinities() const
{
    return __data->getAffinities();
}

QString Quest::getText() const
{
    QStringList affinityTexts;
    foreach (AffinityTypes type, getAffinities()) {
        affinityTexts << QString("%1 (%2)").arg(affinityString(type)).arg(coolNumericFormat(getAffinityPower(type)));
    }
    QString affinityText = affinityTexts.join(", ");
    QTime time;
    return QString("Time: %1\n%2").arg(time.addMSecs(getTime()).toString()).arg(affinityText);
}

QPixmap Quest::getPixmap() const
{
return __data->getPixmap();
}

void Quest::reset()
{
    __data.detach();
    __data->set(qrand());
}

void Quest::setQuestTrigger(QObject *obj, const char *member)
{
    __data->addObj(obj, member);
}
