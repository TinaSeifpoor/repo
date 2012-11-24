#include "measureinterestpointdetectors.h"

int main()
{
    typedef const std::string string;
    typedef std::vector<const std::string> stringList;
    typedef cv::Mat RepeatabilityMatrix;
    typedef std::vector<RepeatabilityMatrix> RepeatabilityMatrixList;

    stringList kuzeyImagePathListGauss,
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

    RepeatabilityMatrixList repeatabilityMatrixList;
    stringList nameList;
    MeasureInterestPointDetectors mipd(kuzeyImagePathListGauss, kuzeyImagePathListQuality,
                        grafittiImagePathList, grafittiHomographyPathList);
    repeatabilityMatrixList.push_back(mipd.measureRepeatability(VisionManager::fdtSift));
    nameList.push_back("Sift Repeatability");
    repeatabilityMatrixList.push_back(mipd.measureRepeatability(VisionManager::fdtHarris));
    nameList.push_back("Harris Repeatability");
    repeatabilityMatrixList.push_back(mipd.measureRepeatability(VisionManager::fdtStar));
    nameList.push_back("Star Repeatability");
    stringList header;
    header.push_back("Repeatability Report");
    header.push_back("Repeatability List goes as");
    header.push_back("Kuzey Gauss03 - Kuzey Gauss05");
    header.push_back("Kuzey Gauss07 - Kuzey Gauss09");
    header.push_back("Kuzey Gauss11 - Kuzey Quality 80");
    header.push_back("Kuzey Quality 60 - Kuzey Quality 30");
    header.push_back("Kuzey Quality 10 - Kuzey Quality 5");
    header.push_back("Grafitti 2 - Grafitti 3");
    header.push_back("Grafitti 4 - Grafitti 5");
    header.push_back("Grafitti 6");
    mipd.writeRepeatabilityOutput(repeatabilityMatrixList, nameList, "repeatabilityResults.yml",header);

    return 0;
}
