#include "source.h"
#include "listrandomsorter.h"
#include "features.h"
#include  <QFile>
struct SourcePrivate {
    QList<Sample> sampleList;
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

Source::~Source()
{
    delete d;
}

Source *Source::baggedSamples(double sampleRatio) const
{
    if (sampleRatio == 1)
        return new Source(d->sampleList);
    else {
        QList<Sample> baggedSampleList = randomlySortList(sampleRatio,d->sampleList);
        return new Source(baggedSampleList);
    }
}


int Source::countSamples() const
{
    return d->sampleList.count();
}

int Source::countClasses() const
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

QHash<int, ClassID> Source::uniqueClasses() const
{
    QHash<int, ClassID> uniqueClassHash;
    for (int i=0; i<d->uniqueClassIDList.size(); ++i) {
        uniqueClassHash.insert(i, d->uniqueClassIDList.at(i));
    }
    return uniqueClassHash;
}

QHash<QString, ClassID> Source::getSampleID() const
{
    QHash<QString, ClassID> sampleIDHash;
    if (d->classIDList.empty())
        getSampleClasses();
    for (int i=0; i<d->classIDList.size(); ++i) {
        sampleIDHash.insert(d->sampleList.at(i).sampleId, d->sampleList.at(i).sampleClass);
    }
    return sampleIDHash;
}

Sample *Source::at(int idx) const
{
    return &d->sampleList[idx];
}

bool Source::writeToDisk(Features* features, QString filePath)
{
    features->setSource(this);
    QString out;
    for (int i=0; i<this->countSamples(); ++i) {
        QStringList values;
        values << at(i)->sampleId;
        values << QString::number(at(i)->sampleClass);
        for (int j=0; j<features->range(); ++j) {
            values << QString::number(at(i)->featureValues.value(j));
        }
        out.append(values.join("\t"));
        out.append("\r\n");
    }
    QFile file(filePath);
    if (file.open(QFile::WriteOnly)) {
        if (file.write(out.toLatin1())) {
            file.close();
            return true;
        }
        file.close();
    }
    return false;
}
