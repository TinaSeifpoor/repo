#include "MyBBEvaluator.h"

using namespace cv;
MyBBEvaluator::MyBBEvaluator(QObject *parent) :
    QObject(parent)
{
}

EvaluationModel MyBBEvaluator::evaluate(QFileInfo imInfo, Mat im, QVector<Rect> bbVec)
{
    EvaluationModel curr;
    curr.imFileInfo = imInfo;
    Mat imBB(im.rows, im.cols, CV_8U);
    imBB = Scalar(0);
    Mat imGT = imBB.clone();
    float bestScore=0;
    Rect bestBB;
    Rect gt = this->groundTruth(imInfo);
    rectangle(imGT, gt, Scalar(255), -1);
    foreach (Rect bb, bbVec)
    {
        rectangle(imBB, bb, Scalar(255),-1);
        int areaUnion = countNonZero(imBB+imGT);
        int areaInter = countNonZero(imBB&imGT);
        float currScore = float(areaInter)/areaUnion;
        if (currScore > bestScore)
        {
            bestScore =currScore;
            bestBB = bb;
        }
    }
    curr.AO = bestScore;
    curr.imToShow = im.clone();
    rectangle(curr.imToShow, gt, Scalar(0,255,0), 2);
    rectangle(curr.imToShow, bestBB, Scalar(0,0,255), 2);
    return curr;
}

Rect MyBBEvaluator::groundTruth(QFileInfo im)
{
//    return Rect(92,83,83,83);
    return Rect(83,92,83,83);
}
