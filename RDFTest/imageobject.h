#ifndef IMAGEOBJECT_H
#define IMAGEOBJECT_H
#include <QVariantHash>
class InstanceObject;
class ImageObjectPrivate;

namespace cv {
class Mat;
}

class ImageObject
{
public:
    ImageObject(QString imagePath);
    ImageObject(QVariantHash data);

    QString name() const;
    InstanceObject* at(int idx);
    int count() const;
    cv::Mat image() const;
    bool isValid() const;
    QString path() const;

    void addInstance(InstanceObject* obj);

    void setName(QString name);
    QVariantHash toHash() const;

private:
    friend class ImageObjectPrivate;
    ImageObjectPrivate* d;
};

#endif // IMAGEOBJECT_H
