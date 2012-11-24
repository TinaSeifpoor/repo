#ifndef MEASUREINTERESTPOINTDETECTORS_H
#define MEASUREINTERESTPOINTDETECTORS_H
#include "visionmanager.h"

class MeasureInterestPointDetectors
{
    typedef std::vector<const std::string> stringList;
    typedef std::vector<double> RepeatabilityList;
    typedef cv::Mat RepeatabilityMatrix;
    typedef std::vector<RepeatabilityMatrix> RepeatabilityMatrixList;
    typedef cv::Mat Image;
    typedef std::vector<Image> ImageList;
    typedef cv::Mat Homography;
    typedef std::vector<cv::Mat> HomographyList;
    typedef unsigned int uint;
    typedef std::string string;
    typedef VisionManager::FeatureDetectorType FeatureDetectorType;

public:
    MeasureInterestPointDetectors(stringList kuzeyImagePathListGauss, stringList kuzeyImagePathListQuality,
                     stringList grafittiImagePathList  , stringList grafittiHomographyPathList);
    RepeatabilityMatrix measureRepeatability(FeatureDetectorType fdt);

    void writeRepeatabilityOutput(RepeatabilityMatrixList repMatList, stringList nameList, string filePath, stringList header=stringList());

private:

    ImageList readImageList(stringList imagePathList);
    HomographyList readHomographyList(stringList homographyPathList);

    ImageList kuzeyImageListGauss;
    ImageList kuzeyImageListQuality;
    ImageList grafittiImageList;
    HomographyList grafittiHomographyList;

};

#endif // MEASUREINTERESTPOINTDETECTORS_H
