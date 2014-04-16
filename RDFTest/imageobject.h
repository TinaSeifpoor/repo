#ifndef IMAGEOBJECT_H
#define IMAGEOBJECT_H

#include <QString>
class InstanceObject;
class ImageObjectPrivate;
namespace cv {
class Mat;
}
class ImageObject
{
public:
    ImageObject(QString imagePath);
    QString name() const;
    InstanceObject* at(int idx);
    int count() const;
    cv::Mat image() const;
    bool isValid() const;

private:
    friend class ImageObjectPrivate;
    ImageObjectPrivate* d;
};

#endif // IMAGEOBJECT_H
