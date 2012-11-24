#ifndef MEASUREINTERESTPOINTDETECTORS_H
#define MEASUREINTERESTPOINTDETECTORS_H
#include "visionmanager.h"

class MeasureInterestPointDetectors
{
    typedef std::vector<const std::string> StringList;
    typedef std::vector<double> RepeatabilityList;
    typedef cv::Mat RepeatabilityMatrix;
    typedef cv::Mat Image;
    typedef std::vector<Image> ImageList;
    typedef cv::Mat Homography;
    typedef std::vector<cv::Mat> HomographyList;
    typedef unsigned int uint;
    typedef std::string string;
    typedef VisionManager::FeatureDetectorType FeatureDetectorType;

public:
    MeasureInterestPointDetectors(StringList kuzeyImagePathListGauss, StringList kuzeyImagePathListQuality,
                     StringList grafittiImagePathList  , StringList grafittiHomographyPathList);
    RepeatabilityMatrix measureRepeatability(FeatureDetectorType fdt);

    void writeRepeatabilityOutput(RepeatabilityMatrix repMat, string filePath);

private:

    ImageList readImageList(StringList imagePathList);
    HomographyList readHomographyList(StringList homographyPathList);

    ImageList kuzeyImageListGauss;
    ImageList kuzeyImageListQuality;
    ImageList grafittiImageList;
    HomographyList grafittiHomographyList;

};

#endif // MEASUREINTERESTPOINTDETECTORS_H
