#include "common.h"
#include "qmath.h"
#include <QApplication>
#include <QLabel>
#include "minion.h"
#include "quest.h"
QList<AffinityTypes> affinityList = QList<AffinityTypes>() << Earth << Nature << Fire << Death << Water << Air;
#define eachaffinity(var) (foreach (AffinityTypes var, affinityList) )
QHash<QPair<AffinityTypes, AffinityTypes>, double> affinityConversionRatios;
#define affPair(t1, t2) (qMakePair<AffinityTypes,AffinityTypes>(t1,t2))

struct affinityPair
{
    QList<AffinityTypes> affinities;
    QList<double> conversionRatios;
    const affinityPair& gen(AffinityTypes type) {
        foreach (AffinityTypes corType, affinityList) {
            if (type == corType) {
                conversionRatios << 1;
                affinities << corType;
            } else if (affinityConversionRatios.contains(affPair(type, corType))){
                conversionRatios << affinityConversionRatios.value(affPair(type, corType));
                affinities << corType;
            } else if (affinityConversionRatios.contains(affPair(corType,type))){
                conversionRatios << affinityConversionRatios.value(affPair(corType, type));
                affinities << corType;
            } else {
                qWarning(QString("affinityPair::gen(): No matching affinity: %1 / %2").arg(type).arg(corType).toLatin1());
            }
            return *this;
        }
    }
};

void initAffinities()
{
    if (affinityConversionRatios.isEmpty()) {
        affinityConversionRatios.insert(affPair(Earth,Nature), 0.8);
        affinityConversionRatios.insert(affPair(Earth,Fire), 0.6);
        affinityConversionRatios.insert(affPair(Earth,Death), 0.4);
        affinityConversionRatios.insert(affPair(Earth,Water), 0.2);
        affinityConversionRatios.insert(affPair(Earth,Air), 0);

        affinityConversionRatios.insert(affPair(Nature,Fire), 0.2);
        affinityConversionRatios.insert(affPair(Nature,Death), 0);
        affinityConversionRatios.insert(affPair(Nature,Water), 0.6);
        affinityConversionRatios.insert(affPair(Nature,Air), 0.4);

        affinityConversionRatios.insert(affPair(Fire,Death), 0.8);
        affinityConversionRatios.insert(affPair(Fire,Water), 0);
        affinityConversionRatios.insert(affPair(Fire,Air), 0.4);

        affinityConversionRatios.insert(affPair(Death,Water), 0.4);
        affinityConversionRatios.insert(affPair(Death,Air), 0.4);
    }
}

unsigned numDigits(const unsigned n) {
    if (n < 10) return 1;
    return 1 + numDigits(n / 10);
}


QList<AffinityTypes> allAffinityList()
{
    return affinityList;
}


QColor affinityToColor(AffinityTypes type) {
    switch (type) {
    case Air:
        return QColor(186,192,191);
    case Earth:
        return QColor(100,82,42);
    case Water:
        return QColor(30,134,219);
    case Fire:
        return QColor(216,106,30);
    case Death:
        return QColor(24,24,24);
    case Nature:
        return QColor(27,64,20);
//    case Base:
//        return QColor(127,127,127);
    }
    return QColor();

}

QString affinityString(AffinityTypes affinity)
{
    switch (affinity) {
    case Air:
        return QApplication::tr("Air");
    case Earth:
        return QApplication::tr("Earth");
    case Water:
        return QApplication::tr("Water");
    case Fire:
        return QApplication::tr("Fire");
    case Death:
        return QApplication::tr("Death");
    case Nature:
        return QApplication::tr("Nature");
//    case Base:
//        return QApplication::tr("Base");
    }
    return QString();
}

QList<AffinityTypes> genAffinities(AffinityTypes base)
{
    initAffinities();
    affinityPair pair;
    pair.gen(base);
    QList<AffinityTypes> affinities;
    for (int i=0; i< pair.conversionRatios.count(); ++i) {
        if (qrand()%100 < pair.conversionRatios.value(i)*100) {
            affinities << pair.affinities.value(i);
        }
    }
    return affinities;
}


QColor affinityToColor(QList<AffinityTypes> affinityList) {
    double red = 0;
    double green = 0;
    double blue = 0;
    foreach (AffinityTypes affinity, affinityList) {
        QColor pureColor = affinityToColor(affinity);
        red+=pureColor.red();
        green+=pureColor.green();
        blue+=pureColor.blue();
    }
    int nAffinities = affinityList.count();
    red/=nAffinities;
    green/=nAffinities;
    blue/=nAffinities;
    return QColor(red,green,blue);
}

QStringList affinityStringList(QList<AffinityTypes> affinityList)
{
    QStringList affinityTextList;
    foreach (AffinityTypes affinity, affinityList)
        affinityTextList << affinityString(affinity);
    return affinityTextList;
}

QStringList numericIdentifier = QStringList()<<"k"<< "m"<< "b" << "t" << "aa" << "bb" << "cc" << "dd" << "ee" << "ff" << "gg" << "hh" << "ii";

QString coolFormat(double numeric, int iteration) {
    double remainingNumeric = qRound64(numeric / 100) / 10.0;
    bool isRound = qint64(remainingNumeric * 10) %10 == 0;//true if the decimal part is equal to 0 (then it's trimmed anyway)
    return (remainingNumeric < 1000? //this determines the class, i.e. 'k', 'm' etc
                                     (QString("%1%2").arg(remainingNumeric > 99.9 || isRound || (!isRound && remainingNumeric > 9.99)? //this decides whether to trim the decimals
                                                                                                                                       (double) remainingNumeric * 10 / 10 : remainingNumeric // (int) d * 10 / 10 drops the decimal
                                                                                                                                       ).arg(numericIdentifier.value(iteration,"INF")))
                                   : coolFormat(remainingNumeric, iteration+1));

}

QString coolNumericFormat(double number)
{
    if (number<1000)
        return QString::number(number);
    return coolFormat(number,0);
}


QString affinityIconString(AffinityTypes affinity)
{
    switch (affinity) {
    case Air:
        return ":/icons/affinity/15/airIcon";
    case Earth:
        return ":/icons/affinity/15/earthIcon";
    case Water:
        return ":/icons/affinity/15/waterIcon";
    case Fire:
        return ":/icons/affinity/15/fireIcon";
    case Death:
        return ":/icons/affinity/15/deathIcon";
    case Nature:
        return ":/icons/affinity/15/natureIcon";
//    case Base:
//        return ":/icons/affinity/15/baseIcon";
    }
    return QString();
}


QLabel *genIconTextLabel(QString iconText, QString text, QWidget *parent) {
    return new QLabel(QString("<html><dl align='middle'><img src='%1'>%2</img></dl></html>").arg(iconText, text),parent);
}


QLabel *genAffinityLabel(Minion minion, AffinityTypes type, QWidget *parent) {
    if (minion.getAffinityPower(type)>0)
        return genIconTextLabel(affinityIconString(type),coolNumericFormat(minion.getAffinityPower(type)),parent);
    else
        return new QLabel(parent);
}

QLabel *genAffinityLabel(Quest quest, AffinityTypes type, QWidget *parent) {
    if (quest.getAffinityPower(type)>0)
        return genIconTextLabel(affinityIconString(type),coolNumericFormat(quest.getAffinityPower(type)),parent);
    else
        return new QLabel(parent);
}


AffinityTypes affinityFromString(QString string)
{
    foreach (AffinityTypes type, allAffinityList())
        if (string == affinityString(type))
            return type;
//    return Base;
}
