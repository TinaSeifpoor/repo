#include "measureinterestpointdetectors.h"
#include <fstream>
using std::string;

MeasureInterestPointDetectors::MeasureInterestPointDetectors(stringList kuzeyImagePathListGauss, stringList kuzeyImagePathListQuality,
                                   stringList grafittiImagePathList, stringList grafittiHomographyPathList)
{
    this->kuzeyImageListGauss = this->readImageList(kuzeyImagePathListGauss);
    this->kuzeyImageListQuality = this->readImageList(kuzeyImagePathListQuality);
    this->grafittiImageList = this->readImageList(grafittiImagePathList);
    this->grafittiHomographyList = this->readHomographyList(grafittiHomographyPathList);
}

MeasureInterestPointDetectors::RepeatabilityMatrix MeasureInterestPointDetectors::measureRepeatability(FeatureDetectorType fdt)
{
    RepeatabilityMatrix repeatabilityMatrix(5,3, CV_64F);

    VisionManager vm;
    uint idxSet = 0;
    Homography identity = Homography::eye(3, 3, CV_64F);
    for (uint idx=1; idx<this->kuzeyImageListGauss.size(); ++idx)
        repeatabilityMatrix.at<double>(idx-1,idxSet) = vm.testFeatureDetectorRepeatability(kuzeyImageListGauss[0], kuzeyImageListGauss[idx], identity, fdt);
    ++idxSet;

    for (uint idx=1; idx<this->kuzeyImageListQuality.size(); ++idx)
        repeatabilityMatrix.at<double>(idx-1,idxSet) = vm.testFeatureDetectorRepeatability(kuzeyImageListQuality[0], kuzeyImageListQuality[idx], identity, fdt);
    ++idxSet;

    for (uint idx=1; idx<this->grafittiImageList.size(); ++idx)
        repeatabilityMatrix.at<double>(idx-1,idxSet) = vm.testFeatureDetectorRepeatability(grafittiImageList[0], grafittiImageList[idx], grafittiHomographyList[idx-1], fdt);
    ++idxSet;


    return repeatabilityMatrix;
}

void MeasureInterestPointDetectors::writeRepeatabilityOutput(RepeatabilityMatrixList repMatList, stringList nameList, string filePath)
{
    using namespace cv;
    FileStorage fs(filePath, FileStorage::WRITE);
    while (!repMatList.empty() && !nameList.empty())
    {
        fs << nameList.back() << repMatList.back();
        nameList.pop_back();
        repMatList.pop_back();
    }

}

MeasureInterestPointDetectors::ImageList MeasureInterestPointDetectors::readImageList(stringList imagePathList)
{
    ImageList imList;
    for (stringList::iterator imagePathListIt=imagePathList.begin(); imagePathListIt!=imagePathList.end(); ++imagePathListIt)
    {
        imList.push_back(cv::imread(*imagePathListIt));
    }
    return imList;
}

MeasureInterestPointDetectors::HomographyList MeasureInterestPointDetectors::readHomographyList(stringList homographyPathList)
{
    // For ifstream...
    using namespace std;

    HomographyList homographyList;
    for (stringList::iterator homographyPathListIt=homographyPathList.begin(); homographyPathListIt!=homographyPathList.end();
         ++homographyPathListIt)
    {
        Homography homography(3,3,CV_64F);
        ifstream dataFile((*homographyPathListIt).c_str());
        for (uint idxRow=0; idxRow<3; ++idxRow)
        {
            for (uint idxCol=0; idxCol<3; ++idxCol)
            {
                double val;
                dataFile >> val;
                homography.at<double>(idxRow, idxCol) = val;
            }
        }
        homographyList.push_back(homography);
    }
    return homographyList;

}
