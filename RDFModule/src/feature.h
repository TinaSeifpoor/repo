#ifndef FEATURE_H
#define FEATURE_H
class Feature
{
public:
    virtual unsigned int parameterRange() const=0;
    virtual Feature* getIndex(const unsigned int idx) const=0;
    virtual double getParameterValue(bool *res=0) const {(void)res;return -1;}
    virtual double parameterValue(int featureIdx, bool *res) const=0;
};

#endif // FEATURE_H
