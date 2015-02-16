#include "common.h"
#include <QColor>
#include "qmath.h"
#include <QApplication>
unsigned numDigits(const unsigned n) {
    if (n < 10) return 1;
    return 1 + numDigits(n / 10);
}


QList<AffinityTypes> allAffinityList()
{
    return QList<AffinityTypes>() <<
                                Air <<
                                Earth <<
                                Water <<
                                Fire <<
                                Death <<
                                Nature;
}


QColor pureAffinityColor(AffinityTypes type) {
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
    }
    return QColor();

}



QList<AffinityTypes> toAffinityList(Affinities affinities)
{
    QList<AffinityTypes> ret;
    QList<AffinityTypes> allAffinities = allAffinityList();
    foreach (AffinityTypes current, allAffinities)
        if (affinities&current)
            ret << current;
    return ret;
}

QString affinityString(AffinityTypes type)
{
    switch (type) {
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
    }
    return QString();
}

Affinities genAffinities(int seed)
{
    int nAffinities = 5 - ceil(((double)numDigits(seed))/2);
    QList<AffinityTypes> allAffinities = allAffinityList();
    Affinities affinities;
    for (int idxAffinity = 1; idxAffinity<nAffinities; ++idxAffinity)
        affinities|=allAffinities.takeAt(seed%allAffinities.count());
    return affinities;
}


double genValue(int seed)
{
    return qPow(2,10 - numDigits(seed));
}


QColor affinityToColor(Affinities type) {
    double red = 0;
    double green = 0;
    double blue = 0;
    QList<AffinityTypes> affinityList = toAffinityList(type);
    foreach (AffinityTypes affinity, affinityList) {
            QColor pureColor = pureAffinityColor(affinity);
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

QStringList affinityStringList(Affinities type)
{
    QStringList affinityTextList;
    foreach (AffinityTypes affinity, toAffinityList(type))
        affinityTextList << affinityString(affinity);
    return affinityTextList;
}
