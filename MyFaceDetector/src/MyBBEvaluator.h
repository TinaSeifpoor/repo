#ifndef MYBBEVALUATOR_H
#define MYBBEVALUATOR_H

#include <QObject>
#include <QFileInfo>
#include <cv.hpp>
#include <QVector>
struct EvaluationModel
{
    double AO;
    cv::Mat imToShow;
    QFileInfo imFileInfo;
    QString type;
};

class MyBBEvaluator : public QObject
{
    Q_OBJECT
public:
    explicit MyBBEvaluator(QObject *parent = 0);
    EvaluationModel evaluate(QFileInfo imInfo, cv::Mat im, QVector<cv::Rect> bbVec);

signals:
    
public slots:
    
private:
    cv::Rect groundTruth(QFileInfo im);
};

#endif // MYBBEVALUATOR_H
