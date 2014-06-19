#ifndef FEATURE_H
#define FEATURE_H
class Sample;
class Feature
{
public:
    virtual unsigned int parameterRange() const=0;
    virtual double parameterValue(unsigned int featureIdx, Sample sample) const=0;
};

#endif // FEATURE_H
