#ifndef CIHANGOLDENLANDMARK_H
#define CIHANGOLDENLANDMARK_H
#include "cihan_global.h"
namespace cv{
class Mat;
}
class CGoldenLandmarkPrivate;

namespace CihanLib {

typedef cv::Mat LandmarkMat;
class CIHANLIBRARYSHARED_EXPORT CGoldenLandmark
{
public:
    CGoldenLandmark(QString filepath);
    bool load();
    void truncate(LandmarkMat goldenLandmarks);
    bool save() const;

    LandmarkMat landmarks() const;
    cv::Mat mask() const;
private:
    CGoldenLandmarkPrivate*d;
};
}
#endif // CIHANGOLDENLANDMARK_H
