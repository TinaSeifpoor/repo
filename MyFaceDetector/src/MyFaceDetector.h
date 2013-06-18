#ifndef MYFACEDETECTOR_H
#define MYFACEDETECTOR_H

#include <MyHoughForest.h>
#include <MyFeatureExtractor.h>
#include <MyDecisionForest.h>
#include <MyBBEvaluator.h>
#include <MyBaseLine.h>
#include <QFileInfoList>
class MyFaceDetector : public QObject
{
    Q_OBJECT
public:
    explicit MyFaceDetector(QObject *parent = 0);
    
signals:
    void evaluation(QList<EvaluationModel>);
    
public slots:
    void loadForest(QFileInfo forest);
    void testForest(QFileInfoList imageFiles);
private:
    HoughForest *hf;
    MyDecisionForest *df;
    MyFeatureExtractor *fe;
    MyBBEvaluator *ev;
    MyBaseLine *vj;
};

#endif // MYFACEDETECTOR_H
