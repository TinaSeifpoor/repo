#include "featuretest.h"
#include <QFileInfo>
FeatureTest::FeatureTest(int index):
    index(index)
{
    if (index ==-1)
        range=32*32*32;
    else {
        range=1;
    }
}

double FeatureTest::parameterValue(int featureIdx, bool *res) const
{
    if (featureIdx==-1) {
        if (res)
            *res=true;
    }
    if (this->range>featureIdx){
        if (res)
            *res = true;
        return 5;
    } else {
        if (res)
            *res = false;
        return INT_MIN;
    }
}

unsigned int FeatureTest::parameterRange() const
{
    return this->range;
}

Feature *FeatureTest::getIndex(const unsigned int idx) const
{
    if (this->index==-1 && range>idx) {
        return new FeatureTest(idx);
    } else if (idx == 0){
        return new FeatureTest(index);
    }
    return 0;
}

double FeatureTest::getParameterValue(bool *res) const
{
    return this->parameterValue(0,res);
}

bool FeatureTest::setSource(const Source *samples, const FeatureIdx idxFeature)
{
    for (int idxSamples=0; idxSamples<samples->countSamples(); ++idxSamples) {
        Sample* sample = samples->at(idxSamples);
        QString basename = sample->sampleSource.value<QFileInfo>().baseName();
        if (basename.length()> idxFeature) {
            int c = basename.at(idxFeature).toLower().unicode();
            if (c>=QChar('a').unicode()) {
                sample->featureValues[idxFeature] = c-QChar((char)'a').unicode();
            } else if (c >= QChar((char)"0").unicode()) {
                sample->featureValues[idxFeature] = c-QChar((char)'0').unicode() + QChar((char)'z').unicode();
            }
        } else {
            sample->featureValues.insert(idxFeature,-1);
        }
    }
    return true;
}

//QFileInfo FeatureTest::getSource() const
//{
//    return this->sample;
//}

