#include "featurestest.h"
#include "featuretest.h"
FeaturesTest::FeaturesTest():
    Features()
{
    (*this) << new FeatureTest;
}

FeaturesTest::FeaturesTest(QList<Feature *> featureList):Features(featureList)
{
}

double FeaturesTest::getFeatureValue(int featureIdx) const
{
//    QPair<Feature*, int> featurePair = at(featureIdx);

//    ft = dynamic_cast<FeatureTest*>(featurePair.first);
//    ft->parameterValue(i, sample);
    return 5;
}

QPair<Feature *, int> FeaturesTest::at(int featureIdx) const
{
//    return qMakePair<Feature *,int>(getFullList().at(featureIdx),5);
    QPair<Feature*,int> a;
    return a;
}
