#ifndef INSTANCEOBJECT_H
#define INSTANCEOBJECT_H
#include <QVariantHash>
namespace cv {
class KeyPoint;
class Mat;
}
class InstanceObjectPrivate;
class InstanceObject
{
public:
    InstanceObject(cv::Mat im, cv::KeyPoint keyPoint, QString name);
    InstanceObject(cv::Mat im, cv::KeyPoint keyPoint, int idx);
    InstanceObject(cv::Mat im, QVariantHash data);
    QString name() const;
    cv::KeyPoint getKeyPoint() const;
    cv::Mat getSourceImage() const;

    QVariantHash toHash() const;

    void setName(QString name);

    bool isValid() const;

private:
    friend class InstanceObjectPrivate;
    InstanceObjectPrivate *d;
};

#endif // INSTANCEOBJECT_H
