#ifndef SOURCE_H
#define SOURCE_H
#include <vector>
const double log2 = 0.30102999566398119521373889472449;

typedef unsigned int ClassID;
typedef double FeatureValue;
typedef double EntropyValue;
class Features;
class Source // A file that contains a training matrix, a directory from which features are read etc.
{
public:
    virtual unsigned int countSamples() = 0;
    virtual unsigned int countFeatures() = 0;
    virtual unsigned int countClasses() = 0;
    virtual Source* baggedSamples(double sampleRatio, double featureRatio) const = 0;
    virtual Features* getFeatures() =0;
    virtual std::vector<double> getFeatureValues(unsigned int idxFeature);
    virtual std::vector<ClassID> getSampleClasses() = 0;
};

#endif // SOURCE_H
