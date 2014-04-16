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
    ImageObject(QVariantHash ini);

    QString name() const;
    InstanceObject* at(int idx);
    int count() const;
    cv::Mat image() const;
    bool isValid() const;

    QVariantHash toIni() const;

private:
    friend class ImageObjectPrivate;
    ImageObjectPrivate* d;
};

#endif // IMAGEOBJECT_H
