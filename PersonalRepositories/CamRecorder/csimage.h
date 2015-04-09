#ifndef CSIMAGE_H
#define CSIMAGE_H

class QImage;
namespace cv{class Mat;}
class CSImagePrivate;
class CSImage
{
    friend class CSImagePrivate;
    CSImagePrivate*d;
public:
    CSImage(QImage im);
    CSImage(cv::Mat im);
    CSImage(const CSImage& other);
    QImage im() const;
    void setInt(int min, int max);
    double convertValue(unsigned int grayValue) const;
};

#endif // CSIMAGE_H
