#ifndef SOURCETEST_H
#define SOURCETEST_H
#include "../../RDFModule/src/source.h"
#include <QFileInfo>
#include "featurestest.h"
class SourceTestPrivate;
class SourceTest : public Source
{
public:
    SourceTest(QFileInfoList fileInfoList, const FeaturesTest *features);

    unsigned int countSamples() const;
    unsigned int countFeatures() const;
    unsigned int countClasses() const;
    Source* baggedSamples(double sampleRatio, double featureRatio) const;
    const Features *getFeatures() const;
    std::vector<double> getFeatureValues(unsigned int idxFeature) const;
    QList<ClassID> getSampleClasses() const;
private:
    friend class SourceTestPrivate;
    SourceTestPrivate* d;
};

#endif // SOURCETEST_H
