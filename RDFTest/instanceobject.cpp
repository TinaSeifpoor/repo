#include "instanceobject.h"
#include <QVector>
#include "opencv2/nonfree/features2d.hpp"
#include "common.h"
Q_DECLARE_METATYPE(cv::KeyPoint)
Q_DECLARE_METATYPE(cv::Mat)

class InstanceObjectPrivate {
public:
    InstanceObjectPrivate(){
        qRegisterMetaType<cv::Mat>("cv::Mat");
        qRegisterMetaTypeStreamOperators<cv::Mat>("cv::Mat");
        qRegisterMetaType<cv::KeyPoint>("cv::KeyPoint");
        qRegisterMetaTypeStreamOperators<cv::KeyPoint>("cv::KeyPoint");
    }
    QString name;
    cv::Mat description;
    cv::KeyPoint keyPoint;
    cv::Mat image;
    void init() {
        using namespace cv;
        SIFT fd(0, 5, 0.1, 10, 1.6);
        KeyPoints k;
        k.push_back(keyPoint);
        fd.compute(image, k, description);
    }
};

InstanceObject::InstanceObject(Image im, cv::KeyPoint keyPoint, QString name): d(new InstanceObjectPrivate)
{
    d->keyPoint = keyPoint;
    d->image = im;
    d->name = name;
    d->init();
}

InstanceObject::InstanceObject(cv::Mat im, QVariantHash ini): d(new InstanceObjectPrivate)
{
    d->image = im;
    d->name = ini.value("Name").toString();
    d->keyPoint = ini.value("KeyPoint").value<cv::KeyPoint>();
    d->description = ini.value("Description").value<cv::Mat>();
}

InstanceObject::InstanceObject(Image im, cv::KeyPoint keyPoint, int idx): d(new InstanceObjectPrivate)
{
    d->keyPoint = keyPoint;
    d->image = im;
    d->name = QString::number(idx);
    d->init();
}

QString InstanceObject::name() const
{
    return d->name;
}

cv::KeyPoint InstanceObject::getKeyPoint() const
{
    return d->keyPoint;
}

cv::Mat InstanceObject::getSourceImage() const
{
    return d->image;
}

QVariantHash InstanceObject::toIni() const
{
    QVariantHash output;
    QVariantHash instanceHash;
    instanceHash.insert("KeyPoint", QVariant::fromValue<cv::KeyPoint>(this->getKeyPoint()));
    instanceHash.insert("Description", QVariant::fromValue<cv::Mat>(d->description));
    instanceHash.insert("Name", d->name);
    output.insert(this->name(), instanceHash);
    return output;
}
