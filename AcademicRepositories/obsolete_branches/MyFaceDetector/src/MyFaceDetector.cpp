#include "MyFaceDetector.h"

MyFaceDetector::MyFaceDetector(QObject *parent) :
    QObject(parent),
    hf(new HoughForest()),
    fe(new MyFeatureExtractor()),
    df(new MyDecisionForest()),
    ev(new MyBBEvaluator()),
    vj(new MyBaseLine())
{
    hf->setFeatureExtractorModel(fe);
    hf->setDecisionForestModel(df);
}

void MyFaceDetector::loadForest(QFileInfo forest)
{
    QFile f(forest.filePath());
    f.open(QFile::ReadOnly);
    df->readForest(f.readAll());
    f.close();
}

void MyFaceDetector::testForest(QFileInfoList imageFiles)
{
    QString hfStr("hf");
    QString vjStr("vj");
    QList<EvaluationModel> hfe;
    foreach (QFileInfo imageFile, imageFiles)
    {
        cv::Mat im = cv::imread(imageFile.filePath().toStdString());
//        EvaluationModel hfEval = ev->evaluate(imageFile,im,hf->getFace(im));
//        hfEval.type = hfStr;
//        hfe << hfEval;
        EvaluationModel vjEval = ev->evaluate(imageFile,im,vj->getFace(im));
        vjEval.type = vjStr;
        hfe << vjEval;
    }
    emit evaluation(hfe);
}
