#include "measureinterestpointdetectors.h"
#include <fstream>
using std::string;

MeasureInterestPointDetectors::RepeatabilityMatrix MeasureInterestPointDetectors::measureRepeatability(FeatureDetectorType fdt)
{
    RepeatabilityMatrix repeatabilityMatrix(this->imageListList[0].size()-1,this->imageListList.size(), CV_64F);

    VisionManager vm;
    for (uint idxSet=0; idxSet<this->imageListList.size(); ++idxSet)
        for (uint idxIns=1; idxIns<this->imageListList[idxSet].size(); ++idxIns)
            repeatabilityMatrix.at<double>(idxIns-1,idxSet) = vm.testFeatureDetectorRepeatability(this->imageListList[idxSet][0],
                                                                                                  this->imageListList[idxSet][idxIns],
                                                                                                  this->homographyListList[idxSet][idxIns-1], fdt);

    return repeatabilityMatrix;
}

void MeasureInterestPointDetectors::loadData(stringListList imagePathListList, stringListList homographyPathListList)
{
    for (uint idxSet=0; idxSet<imagePathListList.size(); ++idxSet)
    {
        HomographyList homographyList;
        imageListList.push_back(this->readImageList(imagePathListList[idxSet]));
        if (!homographyPathListList[idxSet].empty())
        {
            homographyList = this->readHomographyList(homographyPathListList[idxSet]);
        }
        else
        {
            Homography homography=Homography::eye(3,3,CV_64F);
            for (uint idxIm=1; idxIm<imagePathListList[idxSet].size(); ++idxIm)
            {
                homographyList.push_back(homography);
            }
        }
        homographyListList.push_back(homographyList);
    }
}

void MeasureInterestPointDetectors::writeRepeatabilityOutput(RepeatabilityMatrixList repMatList, stringList nameList, string filePath, stringList header)
{
    using namespace cv;
    FileStorage fs(filePath, FileStorage::WRITE);
    fs << "Header" << "[";
    for (uint idx=0; idx<header.size(); ++idx)
    {
        fs << header[idx];
    }
    fs << "]";
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
