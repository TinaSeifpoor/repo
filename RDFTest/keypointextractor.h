#ifndef KEYPOINTEXTRACTOR_H
#define KEYPOINTEXTRACTOR_H
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "common.h"
class KeyPointExtractor
{
public:
    static KeyPoints extract(Image im)
    {
        using namespace cv;
        KeyPoints keyPoints;
//        SiftFeatureDetector(im, im, keyPoints);
        uint nChannels = im.channels();
        Image imageGray;
        uint nCols = im.cols,
             nRows = im.rows;
        Image imMask = Image(nRows, nCols, CV_8UC1, Scalar(255));

        // TODO should consider calculating key points from color space, like lab instead of just gray
        if (nChannels == 3)
            cvtColor(im, imageGray, CV_BGR2GRAY);
        else
            im.copyTo(imageGray);
        SIFT fd;
        fd.detect(imageGray, keyPoints, imMask);
        return keyPoints;
    }

private:
    KeyPointExtractor() {}

};

#endif // KEYPOINTEXTRACTOR_H
