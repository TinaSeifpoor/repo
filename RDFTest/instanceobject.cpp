#include "instanceobject.h"
#include <QVector>
#include "opencv2/nonfree/features2d.hpp"
#include "common.h"
#include <QApplication>
Q_DECLARE_METATYPE(cv::KeyPoint)
Q_DECLARE_METATYPE(cv::Mat)

class InstanceObjectPrivate {
public:
    InstanceObjectPrivate(){
        qRegisterMetaType<cv::Mat>("cv::Mat");
        qRegisterMetaType<cv::KeyPoint>("cv::KeyPoint");
    }
    QString name;
    cv::Mat description;
    cv::KeyPoint keyPoint;
    cv::Mat image;
    bool isValid;
    void init() {
        using namespace cv;
        SIFT fd(0, 5, 0.1, 10, 1.6);
        KeyPoints k;
        k.push_back(keyPoint);
        fd.compute(image, k, description);
        QApplication::processEvents();
    }
};

InstanceObject::InstanceObject(Image im, cv::KeyPoint keyPoint, QString name): d(new InstanceObjectPrivate)
{
    d->keyPoint = keyPoint;
    d->image = im;
    d->name = name;
    d->init();
}

InstanceObject::InstanceObject(cv::Mat im, QVariantHash data): d(new InstanceObjectPrivate)
{
    if (!data.contains("Name")) {
        d->isValid=false;
        return;
    }
    if (data.contains("KeyPoint")) {
        QVariantHash keyPointHash = data.value("KeyPoint").toHash();
        if (keyPointHash.contains("x") && keyPointHash.contains("y") && keyPointHash.contains("size") &&
                keyPointHash.contains("angle") && keyPointHash.contains("response") && keyPointHash.contains("octave") &&
                keyPointHash.contains("class_id")) {
            d->keyPoint = cv::KeyPoint(keyPointHash.value("x").toFloat(),
                                       keyPointHash.value("y").toFloat(),
                                       keyPointHash.value("size").toFloat(),
                                       keyPointHash.value("angle").toFloat(),
                                       keyPointHash.value("response").toFloat(),
                                       keyPointHash.value("octave").toInt(),
                                       keyPointHash.value("class_id").toInt());
        }
    }
    if (data.contains("Description")) {
        d->description = Common::byteArray2Mat(data.value("Description").toByteArray());
    }
    d->image = im;
    d->name = data.value("Name").toString();
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

QVariantHash InstanceObject::toHash() const
{
    QVariantHash output;
    QVariantHash instanceHash;
    cv::KeyPoint kp = d->keyPoint;
    double x=kp.pt.x,y=kp.pt.y,size=kp.size,angle=kp.angle,response=kp.response;
    int octave=kp.octave,class_id=kp.class_id;
    QVariantHash keyPointHash;
    keyPointHash.insert("x", x);
    keyPointHash.insert("y", y);
    keyPointHash.insert("size", size);
    keyPointHash.insert("angle", angle);
    keyPointHash.insert("response", response);
    keyPointHash.insert("octave", octave);
    keyPointHash.insert("class_id", class_id);
    instanceHash.insert("KeyPoint", keyPointHash);
    instanceHash.insert("Description", Common::mat2ByteArray(d->description));
    instanceHash.insert("Name", d->name);
    output.insert(d->name, instanceHash);
    return output;
}

void InstanceObject::setName(QString name)
{
    d->name=name;
}

bool InstanceObject::isValid() const
{
    return d->isValid;
}

