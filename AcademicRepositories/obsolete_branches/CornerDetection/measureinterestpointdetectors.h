#ifndef MEASUREINTERESTPOINTDETECTORS_H
#define MEASUREINTERESTPOINTDETECTORS_H
#include "visionmanager.h"

class MeasureInterestPointDetectors
{
    // All definitions
    typedef std::vector<const std::string> stringList;
    typedef std::vector<stringList> stringListList;
    typedef std::vector<double> RepeatabilityList;
    typedef cv::Mat RepeatabilityMatrix;
    typedef std::vector<RepeatabilityMatrix> RepeatabilityMatrixList;
    typedef cv::Mat Image;
    typedef std::vector<Image> ImageList;
    typedef std::vector<ImageList> ImageListList;
    typedef cv::Mat Homography;
    typedef std::vector<Homography> HomographyList;
    typedef std::vector<HomographyList> HomographyListList;
    typedef unsigned int uint;
    typedef std::string string;
    typedef VisionManager::FeatureDetectorType FeatureDetectorType;
    // All definitions

public:
    MeasureInterestPointDetectors(){}

    RepeatabilityMatrix measureRepeatability(FeatureDetectorType fdt);

    void loadData(stringListList imagePathListList, stringListList homographyPathListList);

    void writeRepeatabilityOutput(RepeatabilityMatrixList repMatList, stringList nameList, string filePath, stringList header=stringList());

private:

    ImageList readImageList(stringList imagePathList);
    HomographyList readHomographyList(stringList homographyPathList);
    ImageListList imageListList;
    HomographyListList homographyListList;
};

#endif // MEASUREINTERESTPOINTDETECTORS_H
