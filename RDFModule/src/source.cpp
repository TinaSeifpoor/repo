#include "source.h"
#include "listrandomsorter.h"
struct SourcePrivate {
    QList<Sample> sampleList;
    Features* features;
    QList<ClassID> classIDList;
    QList<ClassID> uniqueClassIDList;
};

Source::Source(QList<Sample> samples):d(new SourcePrivate)
{
    d->sampleList = samples;
    for (int i=0; i<d->sampleList.count(); ++i) {
        ClassID c = d->sampleList.at(i).sampleClass;
        if (!d->uniqueClassIDList.contains(c))
            d->uniqueClassIDList.append(c);
        d->classIDList.append(c);
    }
}

Source *Source::baggedSamples(double sampleRatio) const
{
    QList<Sample> baggedSampleList = randomlySortList(sampleRatio,d->sampleList);
    return new Source(baggedSampleList);
}


unsigned int Source::countSamples() const
{
    return d->sampleList.count();
}

unsigned int Source::countClasses() const
{
    return d->uniqueClassIDList.count();
}

QList<ClassID> Source::getSampleClasses() const
{
    if (d->classIDList.isEmpty() && !d->sampleList.isEmpty()) {
        for (int i=0; i<d->sampleList.count(); ++i) {
            ClassID c = d->sampleList.at(i).sampleClass;
            if (!d->uniqueClassIDList.contains(c))
                d->uniqueClassIDList.append(c);
            d->classIDList.append(c);
        }
    }
    return d->classIDList;
}

QHash<unsigned int, ClassID> Source::uniqueClasses() const
{
    QHash<unsigned int, ClassID> uniqueClassHash;
    for (int i=0; i<d->uniqueClassIDList.size(); ++i) {
        uniqueClassHash.insert(i, d->uniqueClassIDList.at(i));
    }
    return uniqueClassHash;
}

Sample *Source::at(int idx) const
{
    return &d->sampleList[idx];
}
