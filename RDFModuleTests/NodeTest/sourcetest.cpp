#include "sourcetest.h"
#include "../../RDFModule/src/listrandomsorter.h"
#include "../../RDFModule/src/features.h"
//class SourceTestPrivate {
//public:
//    SourceTestPrivate() {}
//    Features* features;
//    QFileInfoList fileInfoList;
//    QList<ClassID> classIDList;
//    QList<ClassID> uniqueClassIDList;
//};

//SourceTest::SourceTest(QList<Sample> sampleList, Features *features):
//    d(new SourceTestPrivate)
//{
//    d->sampleList = sampleList;
//    d->features = features;
//}

//unsigned int SourceTest::countSamples() const
//{
//    return d->sampleList.count();
//}

//unsigned int SourceTest::countClasses() const
//{
//    if (d->uniqueClassIDList.isEmpty() && !d->sampleList.isEmpty()){
//        this->countClasses();
//    }
//    return d->uniqueClassIDList.count();
//}

//Source *SourceTest::baggedSamples(double sampleRatio) const
//{

//}

//const Features *SourceTest::getFeatures() const
//{
//    return dynamic_cast<const Features*>(d->features);
//}

//std::vector<double> SourceTest::getFeatureValues(unsigned int idxFeature) const
//{
//    std::vector<double> featureValues;
//    featureValues.resize(d->sampleList.count());
//    std::vector<double>::iterator featureValuesIt = featureValues.begin();
//    std::vector<double>::iterator featureValuesEnd = featureValues.end();

//    d->features->setSource(&d->sampleList);
//    for (int i=0;featureValuesIt!=featureValuesEnd;++featureValuesIt, ++i) {
//        // set source
//        *(featureValuesIt) = d->features->getFeatureValue(idxFeature);
//    }
//    return featureValues;
//}

//QList<ClassID> SourceTest::getSampleClasses() const
//{
//    if (d->classIDList.isEmpty() && !d->sampleList.isEmpty()) {
//        for (int i=0; i<d->sampleList.count(); ++i) {
//            ClassID c = d->sampleList.at(i).sampleClass;
//            if (!d->uniqueClassIDList.contains(c))
//                d->uniqueClassIDList.append(c);
//            d->classIDList.append(c);
//        }
//    }
//    return d->classIDList;
//}
