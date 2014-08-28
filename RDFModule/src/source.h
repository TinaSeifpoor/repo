#ifndef SOURCE_H
#define SOURCE_H
#include <vector>
#include <QList>
#include "common.h"

typedef double EntropyValue;
class Features;
struct SourcePrivate;
class Source // A file that contains a training matrix, a directory from which features are read etc.
{
public:
    Source(QList<Sample> samples);
    ~Source();
    Source* baggedSamples(double sampleRatio) const;

    int countSamples() const;
    int countClasses() const;
    QList<ClassID> getSampleClasses() const;
    QHash<int, ClassID> uniqueClasses() const;
    Sample* at(int idx) const;
private:
    SourcePrivate* d;
};

#endif // SOURCE_H
