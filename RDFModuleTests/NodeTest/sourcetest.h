#ifndef SOURCETEST_H
#define SOURCETEST_H
#include "../../RDFModule/src/source.h"
#include "../../RDFModule/src/source.h"
#include <QFileInfo>

class SourceTestPrivate;
class SourceTest : public Source
{
public:
    SourceTest(QList<Sample> sampleList, Features *features);

    unsigned int countSamples() const;
    unsigned int countClasses() const;
    Source* baggedSamples(double sampleRatio) const;
    const Features *getFeatures() const;
    std::vector<double> getFeatureValues(unsigned int idxFeature) const;
    QList<ClassID> getSampleClasses() const;
};

#endif // SOURCETEST_H
