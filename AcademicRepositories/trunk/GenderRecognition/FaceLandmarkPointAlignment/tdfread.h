#ifndef TDFREAD_H
#define TDFREAD_H

namespace cv {
class Mat;
}
class QString;

class TDFRead
{
public:
    static cv::Mat read(QString filepath);
    static cv::Mat reshapeAndNormalizeLandmarks(cv::Mat landmarkPoints);
};

#endif // TDFREAD_H
