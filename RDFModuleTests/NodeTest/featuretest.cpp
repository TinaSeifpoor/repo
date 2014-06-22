#include "featuretest.h"
#include <QFileInfo>
FeatureTest::FeatureTest()
{

}

double FeatureTest::parameterValue(int featureIdx, QFileInfo sample)
{
    return 5;
}

unsigned int FeatureTest::parameterRange() const
{
    return 6;
}
