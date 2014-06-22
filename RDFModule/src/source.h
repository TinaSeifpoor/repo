#ifndef SOURCE_H
#define SOURCE_H
#include <vector>
#include <QList>
const double log2 = 0.69314718055994530941723212145818;
typedef unsigned int ClassID;
typedef double FeatureValue;
typedef double EntropyValue;
class Features;
class Source // A file that contains a training matrix, a directory from which features are read etc.
{
public:
    virtual unsigned int countSamples() const = 0;
    virtual unsigned int countFeatures() const = 0;
    virtual unsigned int countClasses() const = 0;
    virtual Source* baggedSamples(double sampleRatio, double featureRatio) const = 0;
    virtual const Features* getFeatures() const =0;
    virtual std::vector<double> getFeatureValues(unsigned int idxFeature) const=0;
    virtual QList<ClassID> getSampleClasses() const = 0;
};

#endif // SOURCE_H
