#include "instanceobject.h"
#include <QVector>
#include "opencv2/nonfree/features2d.hpp"
#include "common.h"
class InstanceObjectPrivate {
public:
    InstanceObjectPrivate(){}
    QString name;
    cv::Mat description;
};

InstanceObject::InstanceObject(Image im, cv::KeyPoint keyPoint, QString name): d(new InstanceObjectPrivate)
{
    using namespace cv;
    SIFT fd(0, 5, 0.1, 10, 1.6);
    KeyPoints k;
    k.push_back(keyPoint);
    fd.compute(im, k, d->description);
    d->name = name;
}

InstanceObject::InstanceObject(Image im, cv::KeyPoint keyPoint, int idx): d(new InstanceObjectPrivate)
{
    using namespace cv;
    SIFT fd(0, 5, 0.1, 10, 1.6);
    KeyPoints k;
    k.push_back(keyPoint);
    fd.compute(im, k, d->description);
    d->name = QString::number(idx);
}

QString InstanceObject::name() const
{
    return d->name;
}
