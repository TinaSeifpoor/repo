#ifndef CSIMAGE_H
#define CSIMAGE_H
#include <QExplicitlySharedDataPointer>
#include <QRect>
class QImage;
namespace cv{class Mat;}
class CSImagePrivate;
class QRect;
class CSImage
{
    friend class CSImagePrivate;
    QExplicitlySharedDataPointer<CSImagePrivate>d;
public:
    CSImage();
    CSImage(QImage im);
    CSImage(cv::Mat im);
    CSImage(QString path);
    CSImage(const CSImage& other);
    const CSImage& operator =(const CSImage& other);


    QImage im() const;
    CSImage copy(const QRect reg) const;
    bool isNull() const;
    //
    ~CSImage();
    void setInt(int min, int max);
};

#endif // CSIMAGE_H
