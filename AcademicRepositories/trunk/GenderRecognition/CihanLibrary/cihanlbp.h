#ifndef CIHANLBP
#define CIHANLBP
#include "cihan_global.h"
namespace cv {
class Mat;
}
namespace std{
template<class _Ty,class _Ax = allocator<_Ty> >class vector;
}
class QFileInfo;
class CLBPPrivate;
namespace CihanLib {
class CIHANLIBRARYSHARED_EXPORT CLBP
{
public:
    CLBP(cv::Mat image, int nCellWidth=16, int nCellHeight=16);
    CLBP(QFileInfo imageFile, int nCellWidth=16, int nCellHeight=16);
    CLBP(const CLBP& other);
    ~CLBP();
    std::vector<std::vector<int> > regularCellHistograms() const;
    std::vector<std::vector<int> > uniformCellHistograms() const;
    std::vector<int> regularHistogram() const; // concatenated
    std::vector<int> uniformHistogram() const; // concatenated
    std::vector<double> regularNHistogram() const; // concatenated & normalized (total is 1)
    std::vector<double> uniformNHistogram() const; // concatenated & normalized (total is 1)

    static cv::Mat extractFeaturesOLBP(const cv::Mat& src, int nCellWidth=16, int nCellHeight=16);
private:
    CLBPPrivate*d;
};
}
#endif // CIHANLBP

