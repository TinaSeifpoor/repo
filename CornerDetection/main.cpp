#include "measureinterestpointdetectors.h"

int main()
{
    typedef const std::string string;
    typedef std::vector<const string> stringList;
    typedef std::vector<stringList> stringListList;
    typedef cv::Mat RepeatabilityMatrix;
    typedef std::vector<RepeatabilityMatrix> RepeatabilityMatrixList;

    stringListList imagePathListList;
    stringListList homographyPathListList;


    stringList kuzeyImagePathListGauss,
            kuzeyImagePathListQuality,
            grafittiImagePathList,
            grafittiHomographyPathList,
            kuzeyImagePathListScale;

    // Image lists go from most similar to most distinct for
    // easily recognizable repeatability values

    kuzeyImagePathListGauss.push_back("./data/kuzey.jpg");
    kuzeyImagePathListGauss.push_back("./data/kuzeyG05.jpg");
    kuzeyImagePathListGauss.push_back("./data/kuzeyG10.jpg");
    kuzeyImagePathListGauss.push_back("./data/kuzeyG20.jpg");
    kuzeyImagePathListGauss.push_back("./data/kuzeyG40.jpg");
    kuzeyImagePathListGauss.push_back("./data/kuzeyG80.jpg");

    imagePathListList.push_back(kuzeyImagePathListGauss);
    homographyPathListList.push_back(stringList());

    kuzeyImagePathListQuality.push_back("./data/kuzey.jpg");
    kuzeyImagePathListQuality.push_back("./data/kuzeyQ80.jpg");
    kuzeyImagePathListQuality.push_back("./data/kuzeyQ60.jpg");
    kuzeyImagePathListQuality.push_back("./data/kuzeyQ30.jpg");
    kuzeyImagePathListQuality.push_back("./data/kuzeyQ10.jpg");
    kuzeyImagePathListQuality.push_back("./data/kuzeyQ05.jpg");

    imagePathListList.push_back(kuzeyImagePathListQuality);
    homographyPathListList.push_back(stringList());

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

    imagePathListList.push_back(grafittiImagePathList);
    homographyPathListList.push_back(grafittiHomographyPathList);

    kuzeyImagePathListScale.push_back("./data/kuzey.jpg");
    kuzeyImagePathListScale.push_back("./data/kuzeyS85.jpg");
    kuzeyImagePathListScale.push_back("./data/kuzeyS60.jpg");
    kuzeyImagePathListScale.push_back("./data/kuzeyS40.jpg");
    kuzeyImagePathListScale.push_back("./data/kuzeyS30.jpg");
    kuzeyImagePathListScale.push_back("./data/kuzeyS20.jpg");

    imagePathListList.push_back(kuzeyImagePathListScale);
    homographyPathListList.push_back(stringList());


    RepeatabilityMatrixList repeatabilityMatrixList;
    MeasureInterestPointDetectors mipd;

    mipd.loadData(imagePathListList, homographyPathListList);

    stringList nameList;
    repeatabilityMatrixList.push_back(mipd.measureRepeatability(VisionManager::fdtSift));
    nameList.push_back("Sift");
    repeatabilityMatrixList.push_back(mipd.measureRepeatability(VisionManager::fdtHarris));
    nameList.push_back("Harris");
    repeatabilityMatrixList.push_back(mipd.measureRepeatability(VisionManager::fdtStar));
    nameList.push_back("Star");
    stringList header;
    header.push_back("Repeatability Report");
    mipd.writeRepeatabilityOutput(repeatabilityMatrixList, nameList, "repeatabilityResults.xml",header);

    return 0;
}
