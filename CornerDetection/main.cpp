#include "measureinterestpointdetectors.h"

int main()
{
    typedef const std::string string;
    typedef std::vector<const std::string> StringList;
    typedef cv::Mat RepeatabilityMatrix;

    StringList kuzeyImagePathListGauss,
            kuzeyImagePathListQuality,
            grafittiImagePathList,
            grafittiHomographyPathList;

    kuzeyImagePathListGauss.push_back("./data/kuzey.jpg");
    kuzeyImagePathListGauss.push_back("./data/kuzeyG03.jpg");
    kuzeyImagePathListGauss.push_back("./data/kuzeyG05.jpg");
    kuzeyImagePathListGauss.push_back("./data/kuzeyG07.jpg");
    kuzeyImagePathListGauss.push_back("./data/kuzeyG09.jpg");
    kuzeyImagePathListGauss.push_back("./data/kuzeyG11.jpg");


    kuzeyImagePathListQuality.push_back("./data/kuzey.jpg");
    kuzeyImagePathListQuality.push_back("./data/kuzeyQ05.jpg");
    kuzeyImagePathListQuality.push_back("./data/kuzeyQ10.jpg");
    kuzeyImagePathListQuality.push_back("./data/kuzeyQ30.jpg");
    kuzeyImagePathListQuality.push_back("./data/kuzeyQ60.jpg");
    kuzeyImagePathListQuality.push_back("./data/kuzeyQ80.jpg");


    grafittiImagePathList.push_back("./data/img1.png");
    grafittiImagePathList.push_back("./data/img2.png");
    grafittiImagePathList.push_back("./data/img3.png");
    grafittiImagePathList.push_back("./data/img4.png");
    grafittiImagePathList.push_back("./data/img5.png");
    grafittiImagePathList.push_back("./data/img6.png");


    grafittiHomographyPathList.push_back("./data/H1to2p");
    grafittiHomographyPathList.push_back("./data/H1to3p");
    grafittiHomographyPathList.push_back("./data/H1to4p");
    grafittiHomographyPathList.push_back("./data/H1to5p");
    grafittiHomographyPathList.push_back("./data/H1to6p");

    MeasureInterestPointDetectors mipd(kuzeyImagePathListGauss, kuzeyImagePathListQuality,
                        grafittiImagePathList, grafittiHomographyPathList);
//    RepeatabilityMatrix harrisRepeatability = mipd.measureRepeatability(VisionManager::fdtHarris);
//    RepeatabilityMatrix starRepeatability = mipd.measureRepeatability(VisionManager::fdtStar);
    //    RepeatabilityMatrix siftRepeatability = mipd.measureRepeatability(VisionManager::fdtSift);

    RepeatabilityMatrix a= RepeatabilityMatrix::eye(2,2,CV_64F);
    mipd.writeRepeatabilityOutput(a, "harrisRepeatability.yaml");
//    mipd.writeRepeatabilityOutput(starRepeatability, "starRepeatability.yaml");

    return 0;
}
