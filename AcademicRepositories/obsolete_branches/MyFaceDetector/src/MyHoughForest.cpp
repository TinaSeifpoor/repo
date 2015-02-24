#include "MyHoughForest.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "MyFeatureExtractor.h"
#include <QElapsedTimer>
#include <QVector>
using namespace cv;
HoughForest::HoughForest():
    df(0),
    fe(0)
{
    scaleStep =0.93;
    scaleCount = 5;
    patchOverlap = 0.75;
}

void HoughForest::setFeatureExtractorModel(FeatureExtractorModel *fe)
{
    this->fe = fe;
}

void HoughForest::setDecisionForestModel(DecisionForestModel *df)
{
    this->df = df;
}

HoughForest::HoughForest(float scaleStep, int scaleCount, float patchOverlap):
    scaleStep(scaleStep),
    scaleCount(scaleCount),
    patchOverlap(patchOverlap)
{
    this->scaleStep = scaleStep;
}

HoughForest::HoughForest(float scaleStep, int scaleCount):
    scaleStep(scaleStep),
    scaleCount(scaleCount)
{
    patchOverlap = 0.75;
}

HoughForest::~HoughForest(){}

QVector<Rect> HoughForest::getFace(QFileInfo imInfo)
{
    if (!imInfo.exists())
    {
        qWarning(QString("Image file \"%1\" could not be found.").arg(imInfo.filePath()).toAscii().constData());
        return QVector<Rect>();
    }

    Image im = imread(imInfo.filePath().toAscii().constData());
    return this->getFace(im);
}

QVector<Rect> HoughForest::getFace(Image im)
{
    Image imCurr=im.clone();
    Point centroidBest;
    float bestScore=-1;
    float bestScale=0;
    float scaleCur = 1;
    for (int idxScale=0; idxScale<this->scaleCount; ++idxScale)
    {
        // TODO: implement translation as well
        scaleCur = pow(scaleStep,idxScale);
        if (scaleCur!=1)
        {
            scaleCur *= scaleStep;
            resize(im, imCurr, Size(0,0), scaleCur, scaleCur);
        }
        else
            imCurr = im;
//        startTime.start();
        QVector<int> patchRows;
        QVector<int> patchCols;
        FeatureMat fm = this->fe->extractFeatMat(imCurr, this->df->forestModel.patchWidth, this->df->forestModel.patchHeight, patchRows, patchCols);
        //imshow("imCurr",imCurr);
        //waitKey(3);
        //        qDebug("Extraction time:");
        Image HoughImage = Image(im.rows+this->df->forestModel.maxOffsetRow, im.cols+this->df->forestModel.maxOffsetCol, CV_32F);
        HoughImage = Scalar(0);
        //        qDebug(QString::number(double(startTime.nsecsElapsed())/1e+6).toAscii().constData());
        //        qDebug("Hough time:");
        //        startTime.restart();
        for (int idxPatch=0; idxPatch<fm.count();++idxPatch)
        {

            int idxRow = patchRows.at(idxPatch), idxCol = patchCols.at(idxPatch);
            this->df->featVec = fm.at(idxPatch);
            this->df->testForestCC();
            double total=0;
            foreach (int count, this->df->cc)
                total+=count;
            for (int idxClass=0; idxClass<this->df->forestModel.nClasses; ++idxClass)
            {
                int idxBBRow = idxRow + this->df->forestModel.patchOffsetsRows[idxClass]+this->df->forestModel.maxOffsetRow;
                int idxBBCol = idxCol + this->df->forestModel.patchOffsetsCols[idxClass]+this->df->forestModel.maxOffsetCol;
                HoughImage.at<float>(idxBBRow, idxBBCol) +=this->df->cc.at(idxClass)/total;
            }
        }
        //    MyFeatureExtractor::reportMat(HoughImage);
        double minVal,maxVal;
        Point idxMin,idxMax;
        //        HoughImage = HoughImage / fm.count();
        //        GaussianBlur(HoughImage, HoughImage, Size(41,41), 3);
        minMaxLoc(HoughImage, &minVal, &maxVal, &idxMin, &idxMax);
        //        idxMaxList << idxMax;
        //        maxValList << maxVal;
        if (bestScore<maxVal)
        {
            centroidBest = idxMax;
            bestScore = maxVal;
            bestScale = scaleCur;
        }
        //        isGettingBetter = maxVal>(lastScore-0.1);
        //        Image imToShow=imCurr.clone();
        //        rectangle(imToShow, Rect(idxMax.y-48,idxMax.x-48,64,64), Scalar(0,0,255),2);
        //        imshow("Hough", HoughImage);
        //        imshow("Im", imToShow);
        //        waitKey(0);
    }
    //    offset = sqrt(pow(idxMax.x-3,2) + pow(idxMax.y-3,2));
    //    HoughImage = HoughImage*16;
    //    HoughImage.convertTo(HoughImage, CV_8U);
    //    qDebug(QString("Current Point: (%1,%2). Offset: %3").arg(QString::number(idxMax.x)).arg(QString::number(idxMax.y)).arg(QString::number(offset)).toAscii().constData());
//    qDebug(QString::number(double(startTime.nsecsElapsed())/1e+6).toAscii().constData());
    float scaleBack;
    if (bestScale == 1)
        scaleBack =1;
    else
        scaleBack = 1/bestScale;
    //    Image imToShow=im;
    //    rectangle(imToShow, Rect((idxMaxBest.y-48)*scaleBack,(idxMaxBest.x-48)*scaleBack,63*scaleBack*scaleBack,63*scaleBack*scaleBack), Scalar(0,0,255),2);
    //    imshow("Im", imToShow);
//    Image imPerfFound=im.clone();
//    cvtColor(imPerfFound, imPerfFound, CV_RGB2GRAY);
//    imPerfFound = Scalar(0);
//    Image imPerfBB=imPerfFound.clone();

    Rect r((centroidBest.y-this->df->forestModel.maxOffsetCol)*scaleBack,(centroidBest.x-this->df->forestModel.maxOffsetRow)*scaleBack,this->df->forestModel.BBWidth*scaleBack*scaleBack,this->df->forestModel.BBHeight*scaleBack*scaleBack);
    QVector<Rect> rL;
    rL << r;
    return rL;
//    //    rectangle(imPerfBB, Rect(83,92,83,83), Scalar(255),-1);
//    rectangle(imPerfBB, Rect(92,83,83,83), Scalar(255),-1);
//    //    rectangle(imPerfBB, Rect(0,0,63,63), Scalar(255),-1);
//    int areaUnion = countNonZero(imPerfFound+imPerfBB);
//    int areaInter = countNonZero(imPerfFound&imPerfBB);
//    perf = double(areaInter)/areaUnion;
//    if (perf !=1)
//        int a =5;

//    qDebug(QString("Performance: %1").arg(QString::number(perf)).toAscii().constData());
    //    waitKey(0);
    //    return imToShow;
//    return CvContour();
}


