#ifndef FACECROPPER_H
#define FACECROPPER_H
class QString;
class QImage;
#include <QList>
class QRect;
class FaceCropperPrivate;
class FaceCropper
{
    FaceCropperPrivate*d;
public:
    explicit FaceCropper();
    virtual ~FaceCropper();
    bool crop(QImage inputImage, QList<QImage>& outputImages);
    bool crop(QImage inputImage, QList<QRect>& outputRects);
    void setMinNeighbors(int minNeighbors);
    void setMinimumSize(int minimumSize);
    void setScalingFactor(double scalingFactor);

    int minNeighbors() const;
    int minimumSize() const;
    double scalingFactor() const;
};

#endif // FACECROPPER_H
