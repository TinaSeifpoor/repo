#ifndef COMMON_H
#define COMMON_H
#include "cihan_global.h"

namespace cv{
class Mat;
template <typename> class Scalar_;
typedef Scalar_<double> Scalar;
}
#include <QTextStream>
#include <QString>
#include <vector>
namespace CihanLib {

typedef cv::Mat LandmarkMat;
class CIHANLIBRARYSHARED_EXPORT CCommon {
public:
    static void showLandmarks(const LandmarkMat points, cv::Mat& img, cv::Scalar color );
    template <typename tt> static QTextStream & csvWrite(std::vector<tt> valueVector, QTextStream& stream)
    {
        for (size_t i=0; i<valueVector.size()-1; ++i) {
            stream << valueVector.at(i) << ", ";
        }
        stream << valueVector.at(valueVector.size()-1) << "\r\n";
        return stream;
    }};

}
#endif // COMMON_H

