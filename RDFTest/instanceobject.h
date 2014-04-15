#ifndef INSTANCEOBJECT_H
#define INSTANCEOBJECT_H
#include <QString>
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
    QString name() const;
private:
    friend class InstanceObjectPrivate;
    InstanceObjectPrivate *d;
};

#endif // INSTANCEOBJECT_H
