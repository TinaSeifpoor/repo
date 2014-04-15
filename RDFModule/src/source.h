#ifndef SOURCE_H
#define SOURCE_H
class Source // A file that contains a training matrix, a directory from which features are read etc.
{
public:
    virtual unsigned int countSamples() = 0;
    virtual unsigned int countFeatures() = 0;

    virtual Source* baggedSamples(double sampleRatio, double featureRatio) = 0;
};

#endif // SOURCE_H
