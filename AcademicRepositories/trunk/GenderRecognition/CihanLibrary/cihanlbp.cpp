#include "cihanlbp.h"
#include "lbp.hpp"
#include <QFileInfo>


// details at the end of source file for uniformity / transition etc. wikipage is a good reference: https://en.wikipedia.org/wiki/Local_binary_patterns
const bool isUniform[256] = {false, false, false, false, false, true, false, false, false, true, true, true, false, true, false, false, false, true, true, true, true, true, true, true, false, true, true, true, false, true, false, false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, true, true, true, true, true, true, true, false, true, true, true, false, true, false, false, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, true, true, true, true, true, true, true, false, true, true, true, false, true, false, false, false, false, true, false, true, true, true, false, true, true, true, true, true, true, true, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, false, false, true, false, true, true, true, false, true, true, true, true, true, true, true, false, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, false, false, false, true, false, true, true, true, false, true, true, true, true, true, true, true, false, false, false, true, false, true, true, true, false, false, false, true, false, false, false, false, false};
const int uniformBinIndex[256] = {1, 2, 3, 4, 5, 0, 6, 7, 8, 0, 0, 0, 9, 0, 10, 11, 12, 0, 0, 0, 0, 0, 0, 0, 13, 0, 0, 0, 14, 0, 15, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 0, 0, 0, 0, 0, 0, 0, 19, 0, 0, 0, 20, 0, 21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 26, 0, 0, 0, 27, 0, 28, 29, 30, 31, 0, 32, 0, 0, 0, 33, 0, 0, 0, 0, 0, 0, 0, 34, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 37, 38, 0, 39, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 43, 44, 0, 45, 0, 0, 0, 46, 0, 0, 0, 0, 0, 0, 0, 47, 48, 49, 0, 50, 0, 0, 0, 51, 52, 53, 0, 54, 55, 56, 57, 58};
class Essentials
{
public:
    template <typename t>
    static std::vector<t> convertToUniformHistogram(std::vector<t> regular8bitHistogram) {
        std::vector<t> uniformHistogram; // where zero bin is for non-uniform numbers
        uniformHistogram.resize(59,0);
        for (int i=0; i<256; ++i) {
            int uniformIdx = uniformBinIndex[i];
            uniformHistogram.at(uniformIdx) += regular8bitHistogram.at(i);
        }
        return uniformHistogram;
    }

} e;

class CLBPPrivate {
public:
    CLBPPrivate(cv::Mat sourceImage, int nCellWidth, int nCellHeight):
        sourceImage(sourceImage),
        nCellWidth(nCellWidth),
        nCellHeight(nCellHeight)
    {
        cv::Mat dst = lbp::OLBP(sourceImage); // these are values from these two lines:
        // For each pixel in a cell, compare the pixel to each of its 8 neighbors (on its left-top, left-middle, left-bottom, right-top, etc.). Follow the pixels along a circle, i.e. clockwise or counter-clockwise.
        // Where the center pixel's value is greater than the neighbor's value, write "1". Otherwise, write "0". This gives an 8-digit binary number (which is usually converted to decimal for convenience).

        // code:
        //    unsigned char code = 0;
        //    code |= (src.at<_Tp>(i-1,j-1) > center) << 7;
        //    code |= (src.at<_Tp>(i-1,j) > center) << 6;
        //    code |= (src.at<_Tp>(i-1,j+1) > center) << 5;
        //    code |= (src.at<_Tp>(i,j+1) > center) << 4;
        //    code |= (src.at<_Tp>(i+1,j+1) > center) << 3;
        //    code |= (src.at<_Tp>(i+1,j) > center) << 2;
        //    code |= (src.at<_Tp>(i+1,j-1) > center) << 1;
        //    code |= (src.at<_Tp>(i,j-1) > center) << 0;
        //    dst.at<unsigned char>(i-1,j-1) = code;

        for (int xCellStart = 0; xCellStart<dst.cols; xCellStart+=nCellWidth) {
            for (int yCellStart = 0; yCellStart<dst.rows; yCellStart+=nCellHeight) {
                cv::Rect cellRect = cv::Rect(xCellStart, yCellStart, cv::min(nCellWidth, dst.cols-xCellStart), cv::min(nCellHeight, dst.rows-yCellStart));
                cv::Mat cellImage = dst(cellRect);
                std::vector<int> regularCellHistogram;
                regularCellHistogram.resize(256,0);

                std::vector<double> regularCellNHistogram;
                regularCellNHistogram.resize(256,0);
                double step = 1/(double)cellRect.area(); // for normalized (sum to 1) histogram
                for (int xCell = 0; xCell<cellImage.cols; ++xCell) {
                    for (int yCell = 0; yCell<cellImage.rows; ++yCell) {
                        unsigned char lbpForPixel = cellImage.at<unsigned char>(yCell, xCell);
                        ++regularCellHistogram[lbpForPixel];
                        regularCellNHistogram[lbpForPixel]+=step;
                    }
                }

                regularCellNHistograms.push_back(regularCellNHistogram);
                std::vector<double> uniformCellNHistogram = Essentials::convertToUniformHistogram<double>(regularCellNHistogram);
                uniformCellNHistograms.push_back(uniformCellNHistogram);
                regularNHistogram.insert(regularNHistogram.end(), regularCellNHistogram.begin(), regularCellNHistogram.end());
                uniformNHistogram.insert(uniformNHistogram.end(), uniformCellNHistogram.begin(), uniformCellNHistogram.end());


                regularCellHistograms.push_back(regularCellHistogram);
                std::vector<int> uniformCellHistogram = Essentials::convertToUniformHistogram<int>(regularCellHistogram);
                uniformCellHistograms.push_back(uniformCellHistogram);
                regularHistogram.insert(regularHistogram.end(), regularCellHistogram.begin(), regularCellHistogram.end());
                uniformHistogram.insert(uniformHistogram.end(), uniformCellHistogram.begin(), uniformCellHistogram.end());
            }
        }
        for (int i=0; i<uniformHistogram.size();++i) {
            uniformNHistogram.push_back((double)uniformHistogram.at(i) / nCellWidth / nCellHeight);
            regularNHistogram.push_back((double)regularHistogram.at(i) / nCellWidth / nCellHeight);
        }
    }

    CLBPPrivate(const CLBPPrivate& other) {
        sourceImage = other.sourceImage;
        nCellWidth = other.nCellWidth;
        nCellHeight = other.nCellHeight;

        regularCellHistograms = other.regularCellHistograms;
        uniformCellHistograms = other.uniformCellHistograms;
        regularCellNHistograms = other.regularCellNHistograms;
        uniformCellNHistograms = other.uniformCellNHistograms;

        regularHistogram = other.regularHistogram;
        uniformHistogram = other.uniformHistogram;
        regularNHistogram = other.regularNHistogram;
        uniformNHistogram = other.uniformNHistogram;
    }

    cv::Mat sourceImage;
    int nCellWidth;
    int nCellHeight;
    std::vector<std::vector<int> > regularCellHistograms;
    std::vector<std::vector<int> > uniformCellHistograms;
    std::vector<std::vector<double> > regularCellNHistograms;
    std::vector<std::vector<double> > uniformCellNHistograms;
    std::vector<int> regularHistogram; // concatenated
    std::vector<int> uniformHistogram; // concatenated
    std::vector<double> regularNHistogram; // concatenated
    std::vector<double> uniformNHistogram; // concatenated
};
class Essentials;
namespace CihanLib{


CLBP::CLBP(Mat image, int nCellWidth, int nCellHeight):
    d(new CLBPPrivate(image, nCellWidth,nCellHeight))
{

}

CLBP::CLBP(QFileInfo imageFile, int nCellWidth, int nCellHeight):
    d(new CLBPPrivate(cv::imread(imageFile.filePath().toStdString()), nCellWidth, nCellHeight))
{

}

CLBP::CLBP(const CLBP& other):
    d(new CLBPPrivate(*other.d))
{

}

CLBP::~CLBP()
{
    delete d;
}

std::vector<std::vector<int> > CLBP::regularCellHistograms() const
{
    return d->regularCellHistograms;
}

std::vector<std::vector<int> > CLBP::uniformCellHistograms() const
{
    return d->uniformCellHistograms;
}

std::vector<int> CLBP::regularHistogram() const
{
    return d->regularHistogram;
}

std::vector<int> CLBP::uniformHistogram() const
{
    return d->uniformHistogram;
}

std::vector<double> CLBP::regularNHistogram() const
{
    return d->regularNHistogram;
}

std::vector<double> CLBP::uniformNHistogram() const
{
    return d->uniformNHistogram;
}
}



/* Chunk of info
 *
 * Regular 8-bit histogram to irregular, uniform / non-uniform transition histogram, where all non-uniform values are sent to 0th idx (their distinct values don't matter as much)
 * Below is a table where 0,1,2,3 ... 255 are uniform values (and hence have unique bins) and NU is non-uniform and hence have only 0th bin.
 * Excel functions row (for easy computation - reproduction):
 *              0	1	2	3	4	5	6	7		1	2	3	4	5	6	7
 * 0            =MOD(FLOOR($A2/POWER(2,D$1),1),2)   =IF(D2=E2,0,1)              =SUM(M2:S2)>2                       Lookup table (0-58) for uniform & one non-uniform bin => =VLOOKUP(AC2,$AG$2:$AH$60,2)
 *
 * Output:
 *
 * Byte Val,    Regular bit histogram               Transition histogram        Is non-uniform?                     Target bin
 *              0	1	2	3	4	5	6	7		1	2	3	4	5	6	7
 * 0			0	0	0	0	0	0	0	0		0	0	0	0	0	0	0	FALSE								1
 * 1			1	0	0	0	0	0	0	0		1	0	0	0	0	0	0	FALSE								2
 * 2			0	1	0	0	0	0	0	0		1	1	0	0	0	0	0	FALSE								3
 * 3			1	1	0	0	0	0	0	0		0	1	0	0	0	0	0	FALSE								4
 * 4			0	0	1	0	0	0	0	0		0	1	1	0	0	0	0	FALSE								5
 * 5			1	0	1	0	0	0	0	0		1	1	1	0	0	0	0	TRUE								0
 * 6			0	1	1	0	0	0	0	0		1	0	1	0	0	0	0	FALSE								6
 * 7			1	1	1	0	0	0	0	0		0	0	1	0	0	0	0	FALSE								7
 * 8			0	0	0	1	0	0	0	0		0	0	1	1	0	0	0	FALSE								8
 * 9			1	0	0	1	0	0	0	0		1	0	1	1	0	0	0	TRUE								0
 * 10			0	1	0	1	0	0	0	0		1	1	1	1	0	0	0	TRUE								0
 * 11			1	1	0	1	0	0	0	0		0	1	1	1	0	0	0	TRUE								0
 * 12			0	0	1	1	0	0	0	0		0	1	0	1	0	0	0	FALSE								9
 * 13			1	0	1	1	0	0	0	0		1	1	0	1	0	0	0	TRUE								0
 * 14			0	1	1	1	0	0	0	0		1	0	0	1	0	0	0	FALSE								10
 * 15			1	1	1	1	0	0	0	0		0	0	0	1	0	0	0	FALSE								11
 * 16			0	0	0	0	1	0	0	0		0	0	0	1	1	0	0	FALSE								12
 * 17			1	0	0	0	1	0	0	0		1	0	0	1	1	0	0	TRUE								0
 * 18			0	1	0	0	1	0	0	0		1	1	0	1	1	0	0	TRUE								0
 * 19			1	1	0	0	1	0	0	0		0	1	0	1	1	0	0	TRUE								0
 * 20			0	0	1	0	1	0	0	0		0	1	1	1	1	0	0	TRUE								0
 * 21			1	0	1	0	1	0	0	0		1	1	1	1	1	0	0	TRUE								0
 * 22			0	1	1	0	1	0	0	0		1	0	1	1	1	0	0	TRUE								0
 * 23			1	1	1	0	1	0	0	0		0	0	1	1	1	0	0	TRUE								0
 * 24			0	0	0	1	1	0	0	0		0	0	1	0	1	0	0	FALSE								13
 * 25			1	0	0	1	1	0	0	0		1	0	1	0	1	0	0	TRUE								0
 * 26			0	1	0	1	1	0	0	0		1	1	1	0	1	0	0	TRUE								0
 * 27			1	1	0	1	1	0	0	0		0	1	1	0	1	0	0	TRUE								0
 * 28			0	0	1	1	1	0	0	0		0	1	0	0	1	0	0	FALSE								14
 * 29			1	0	1	1	1	0	0	0		1	1	0	0	1	0	0	TRUE								0
 * 30			0	1	1	1	1	0	0	0		1	0	0	0	1	0	0	FALSE								15
 * 31			1	1	1	1	1	0	0	0		0	0	0	0	1	0	0	FALSE								16
 * 32			0	0	0	0	0	1	0	0		0	0	0	0	1	1	0	FALSE								17
 * 33			1	0	0	0	0	1	0	0		1	0	0	0	1	1	0	TRUE								0
 * 34			0	1	0	0	0	1	0	0		1	1	0	0	1	1	0	TRUE								0
 * 35			1	1	0	0	0	1	0	0		0	1	0	0	1	1	0	TRUE								0
 * 36			0	0	1	0	0	1	0	0		0	1	1	0	1	1	0	TRUE								0
 * 37			1	0	1	0	0	1	0	0		1	1	1	0	1	1	0	TRUE								0
 * 38			0	1	1	0	0	1	0	0		1	0	1	0	1	1	0	TRUE								0
 * 39			1	1	1	0	0	1	0	0		0	0	1	0	1	1	0	TRUE								0
 * 40			0	0	0	1	0	1	0	0		0	0	1	1	1	1	0	TRUE								0
 * 41			1	0	0	1	0	1	0	0		1	0	1	1	1	1	0	TRUE								0
 * 42			0	1	0	1	0	1	0	0		1	1	1	1	1	1	0	TRUE								0
 * 43			1	1	0	1	0	1	0	0		0	1	1	1	1	1	0	TRUE								0
 * 44			0	0	1	1	0	1	0	0		0	1	0	1	1	1	0	TRUE								0
 * 45			1	0	1	1	0	1	0	0		1	1	0	1	1	1	0	TRUE								0
 * 46			0	1	1	1	0	1	0	0		1	0	0	1	1	1	0	TRUE								0
 * 47			1	1	1	1	0	1	0	0		0	0	0	1	1	1	0	TRUE								0
 * 48			0	0	0	0	1	1	0	0		0	0	0	1	0	1	0	FALSE								18
 * 49			1	0	0	0	1	1	0	0		1	0	0	1	0	1	0	TRUE								0
 * 50			0	1	0	0	1	1	0	0		1	1	0	1	0	1	0	TRUE								0
 * 51			1	1	0	0	1	1	0	0		0	1	0	1	0	1	0	TRUE								0
 * 52			0	0	1	0	1	1	0	0		0	1	1	1	0	1	0	TRUE								0
 * 53			1	0	1	0	1	1	0	0		1	1	1	1	0	1	0	TRUE								0
 * 54			0	1	1	0	1	1	0	0		1	0	1	1	0	1	0	TRUE								0
 * 55			1	1	1	0	1	1	0	0		0	0	1	1	0	1	0	TRUE								0
 * 56			0	0	0	1	1	1	0	0		0	0	1	0	0	1	0	FALSE								19
 * 57			1	0	0	1	1	1	0	0		1	0	1	0	0	1	0	TRUE								0
 * 58			0	1	0	1	1	1	0	0		1	1	1	0	0	1	0	TRUE								0
 * 59			1	1	0	1	1	1	0	0		0	1	1	0	0	1	0	TRUE								0
 * 60			0	0	1	1	1	1	0	0		0	1	0	0	0	1	0	FALSE								20
 * 61			1	0	1	1	1	1	0	0		1	1	0	0	0	1	0	TRUE								0
 * 62			0	1	1	1	1	1	0	0		1	0	0	0	0	1	0	FALSE								21
 * 63			1	1	1	1	1	1	0	0		0	0	0	0	0	1	0	FALSE								22
 * 64			0	0	0	0	0	0	1	0		0	0	0	0	0	1	1	FALSE								23
 * 65			1	0	0	0	0	0	1	0		1	0	0	0	0	1	1	TRUE								0
 * 66			0	1	0	0	0	0	1	0		1	1	0	0	0	1	1	TRUE								0
 * 67			1	1	0	0	0	0	1	0		0	1	0	0	0	1	1	TRUE								0
 * 68			0	0	1	0	0	0	1	0		0	1	1	0	0	1	1	TRUE								0
 * 69			1	0	1	0	0	0	1	0		1	1	1	0	0	1	1	TRUE								0
 * 70			0	1	1	0	0	0	1	0		1	0	1	0	0	1	1	TRUE								0
 * 71			1	1	1	0	0	0	1	0		0	0	1	0	0	1	1	TRUE								0
 * 72			0	0	0	1	0	0	1	0		0	0	1	1	0	1	1	TRUE								0
 * 73			1	0	0	1	0	0	1	0		1	0	1	1	0	1	1	TRUE								0
 * 74			0	1	0	1	0	0	1	0		1	1	1	1	0	1	1	TRUE								0
 * 75			1	1	0	1	0	0	1	0		0	1	1	1	0	1	1	TRUE								0
 * 76			0	0	1	1	0	0	1	0		0	1	0	1	0	1	1	TRUE								0
 * 77			1	0	1	1	0	0	1	0		1	1	0	1	0	1	1	TRUE								0
 * 78			0	1	1	1	0	0	1	0		1	0	0	1	0	1	1	TRUE								0
 * 79			1	1	1	1	0	0	1	0		0	0	0	1	0	1	1	TRUE								0
 * 80			0	0	0	0	1	0	1	0		0	0	0	1	1	1	1	TRUE								0
 * 81			1	0	0	0	1	0	1	0		1	0	0	1	1	1	1	TRUE								0
 * 82			0	1	0	0	1	0	1	0		1	1	0	1	1	1	1	TRUE								0
 * 83			1	1	0	0	1	0	1	0		0	1	0	1	1	1	1	TRUE								0
 * 84			0	0	1	0	1	0	1	0		0	1	1	1	1	1	1	TRUE								0
 * 85			1	0	1	0	1	0	1	0		1	1	1	1	1	1	1	TRUE								0
 * 86			0	1	1	0	1	0	1	0		1	0	1	1	1	1	1	TRUE								0
 * 87			1	1	1	0	1	0	1	0		0	0	1	1	1	1	1	TRUE								0
 * 88			0	0	0	1	1	0	1	0		0	0	1	0	1	1	1	TRUE								0
 * 89			1	0	0	1	1	0	1	0		1	0	1	0	1	1	1	TRUE								0
 * 90			0	1	0	1	1	0	1	0		1	1	1	0	1	1	1	TRUE								0
 * 91			1	1	0	1	1	0	1	0		0	1	1	0	1	1	1	TRUE								0
 * 92			0	0	1	1	1	0	1	0		0	1	0	0	1	1	1	TRUE								0
 * 93			1	0	1	1	1	0	1	0		1	1	0	0	1	1	1	TRUE								0
 * 94			0	1	1	1	1	0	1	0		1	0	0	0	1	1	1	TRUE								0
 * 95			1	1	1	1	1	0	1	0		0	0	0	0	1	1	1	TRUE								0
 * 96			0	0	0	0	0	1	1	0		0	0	0	0	1	0	1	FALSE								24
 * 97			1	0	0	0	0	1	1	0		1	0	0	0	1	0	1	TRUE								0
 * 98			0	1	0	0	0	1	1	0		1	1	0	0	1	0	1	TRUE								0
 * 99			1	1	0	0	0	1	1	0		0	1	0	0	1	0	1	TRUE								0
 * 100			0	0	1	0	0	1	1	0		0	1	1	0	1	0	1	TRUE								0
 * 101			1	0	1	0	0	1	1	0		1	1	1	0	1	0	1	TRUE								0
 * 102			0	1	1	0	0	1	1	0		1	0	1	0	1	0	1	TRUE								0
 * 103			1	1	1	0	0	1	1	0		0	0	1	0	1	0	1	TRUE								0
 * 104			0	0	0	1	0	1	1	0		0	0	1	1	1	0	1	TRUE								0
 * 105			1	0	0	1	0	1	1	0		1	0	1	1	1	0	1	TRUE								0
 * 106			0	1	0	1	0	1	1	0		1	1	1	1	1	0	1	TRUE								0
 * 107			1	1	0	1	0	1	1	0		0	1	1	1	1	0	1	TRUE								0
 * 108			0	0	1	1	0	1	1	0		0	1	0	1	1	0	1	TRUE								0
 * 109			1	0	1	1	0	1	1	0		1	1	0	1	1	0	1	TRUE								0
 * 110			0	1	1	1	0	1	1	0		1	0	0	1	1	0	1	TRUE								0
 * 111			1	1	1	1	0	1	1	0		0	0	0	1	1	0	1	TRUE								0
 * 112			0	0	0	0	1	1	1	0		0	0	0	1	0	0	1	FALSE								25
 * 113			1	0	0	0	1	1	1	0		1	0	0	1	0	0	1	TRUE								0
 * 114			0	1	0	0	1	1	1	0		1	1	0	1	0	0	1	TRUE								0
 * 115			1	1	0	0	1	1	1	0		0	1	0	1	0	0	1	TRUE								0
 * 116			0	0	1	0	1	1	1	0		0	1	1	1	0	0	1	TRUE								0
 * 117			1	0	1	0	1	1	1	0		1	1	1	1	0	0	1	TRUE								0
 * 118			0	1	1	0	1	1	1	0		1	0	1	1	0	0	1	TRUE								0
 * 119			1	1	1	0	1	1	1	0		0	0	1	1	0	0	1	TRUE								0
 * 120			0	0	0	1	1	1	1	0		0	0	1	0	0	0	1	FALSE								26
 * 121			1	0	0	1	1	1	1	0		1	0	1	0	0	0	1	TRUE								0
 * 122			0	1	0	1	1	1	1	0		1	1	1	0	0	0	1	TRUE								0
 * 123			1	1	0	1	1	1	1	0		0	1	1	0	0	0	1	TRUE								0
 * 124			0	0	1	1	1	1	1	0		0	1	0	0	0	0	1	FALSE								27
 * 125			1	0	1	1	1	1	1	0		1	1	0	0	0	0	1	TRUE								0
 * 126			0	1	1	1	1	1	1	0		1	0	0	0	0	0	1	FALSE								28
 * 127			1	1	1	1	1	1	1	0		0	0	0	0	0	0	1	FALSE								29
 * 128			0	0	0	0	0	0	0	1		0	0	0	0	0	0	1	FALSE								30
 * 129			1	0	0	0	0	0	0	1		1	0	0	0	0	0	1	FALSE								31
 * 130			0	1	0	0	0	0	0	1		1	1	0	0	0	0	1	TRUE								0
 * 131			1	1	0	0	0	0	0	1		0	1	0	0	0	0	1	FALSE								32
 * 132			0	0	1	0	0	0	0	1		0	1	1	0	0	0	1	TRUE								0
 * 133			1	0	1	0	0	0	0	1		1	1	1	0	0	0	1	TRUE								0
 * 134			0	1	1	0	0	0	0	1		1	0	1	0	0	0	1	TRUE								0
 * 135			1	1	1	0	0	0	0	1		0	0	1	0	0	0	1	FALSE								33
 * 136			0	0	0	1	0	0	0	1		0	0	1	1	0	0	1	TRUE								0
 * 137			1	0	0	1	0	0	0	1		1	0	1	1	0	0	1	TRUE								0
 * 138			0	1	0	1	0	0	0	1		1	1	1	1	0	0	1	TRUE								0
 * 139			1	1	0	1	0	0	0	1		0	1	1	1	0	0	1	TRUE								0
 * 140			0	0	1	1	0	0	0	1		0	1	0	1	0	0	1	TRUE								0
 * 141			1	0	1	1	0	0	0	1		1	1	0	1	0	0	1	TRUE								0
 * 142			0	1	1	1	0	0	0	1		1	0	0	1	0	0	1	TRUE								0
 * 143			1	1	1	1	0	0	0	1		0	0	0	1	0	0	1	FALSE								34
 * 144			0	0	0	0	1	0	0	1		0	0	0	1	1	0	1	TRUE								0
 * 145			1	0	0	0	1	0	0	1		1	0	0	1	1	0	1	TRUE								0
 * 146			0	1	0	0	1	0	0	1		1	1	0	1	1	0	1	TRUE								0
 * 147			1	1	0	0	1	0	0	1		0	1	0	1	1	0	1	TRUE								0
 * 148			0	0	1	0	1	0	0	1		0	1	1	1	1	0	1	TRUE								0
 * 149			1	0	1	0	1	0	0	1		1	1	1	1	1	0	1	TRUE								0
 * 150			0	1	1	0	1	0	0	1		1	0	1	1	1	0	1	TRUE								0
 * 151			1	1	1	0	1	0	0	1		0	0	1	1	1	0	1	TRUE								0
 * 152			0	0	0	1	1	0	0	1		0	0	1	0	1	0	1	TRUE								0
 * 153			1	0	0	1	1	0	0	1		1	0	1	0	1	0	1	TRUE								0
 * 154			0	1	0	1	1	0	0	1		1	1	1	0	1	0	1	TRUE								0
 * 155			1	1	0	1	1	0	0	1		0	1	1	0	1	0	1	TRUE								0
 * 156			0	0	1	1	1	0	0	1		0	1	0	0	1	0	1	TRUE								0
 * 157			1	0	1	1	1	0	0	1		1	1	0	0	1	0	1	TRUE								0
 * 158			0	1	1	1	1	0	0	1		1	0	0	0	1	0	1	TRUE								0
 * 159			1	1	1	1	1	0	0	1		0	0	0	0	1	0	1	FALSE								35
 * 160			0	0	0	0	0	1	0	1		0	0	0	0	1	1	1	TRUE								0
 * 161			1	0	0	0	0	1	0	1		1	0	0	0	1	1	1	TRUE								0
 * 162			0	1	0	0	0	1	0	1		1	1	0	0	1	1	1	TRUE								0
 * 163			1	1	0	0	0	1	0	1		0	1	0	0	1	1	1	TRUE								0
 * 164			0	0	1	0	0	1	0	1		0	1	1	0	1	1	1	TRUE								0
 * 165			1	0	1	0	0	1	0	1		1	1	1	0	1	1	1	TRUE								0
 * 166			0	1	1	0	0	1	0	1		1	0	1	0	1	1	1	TRUE								0
 * 167			1	1	1	0	0	1	0	1		0	0	1	0	1	1	1	TRUE								0
 * 168			0	0	0	1	0	1	0	1		0	0	1	1	1	1	1	TRUE								0
 * 169			1	0	0	1	0	1	0	1		1	0	1	1	1	1	1	TRUE								0
 * 170			0	1	0	1	0	1	0	1		1	1	1	1	1	1	1	TRUE								0
 * 171			1	1	0	1	0	1	0	1		0	1	1	1	1	1	1	TRUE								0
 * 172			0	0	1	1	0	1	0	1		0	1	0	1	1	1	1	TRUE								0
 * 173			1	0	1	1	0	1	0	1		1	1	0	1	1	1	1	TRUE								0
 * 174			0	1	1	1	0	1	0	1		1	0	0	1	1	1	1	TRUE								0
 * 175			1	1	1	1	0	1	0	1		0	0	0	1	1	1	1	TRUE								0
 * 176			0	0	0	0	1	1	0	1		0	0	0	1	0	1	1	TRUE								0
 * 177			1	0	0	0	1	1	0	1		1	0	0	1	0	1	1	TRUE								0
 * 178			0	1	0	0	1	1	0	1		1	1	0	1	0	1	1	TRUE								0
 * 179			1	1	0	0	1	1	0	1		0	1	0	1	0	1	1	TRUE								0
 * 180			0	0	1	0	1	1	0	1		0	1	1	1	0	1	1	TRUE								0
 * 181			1	0	1	0	1	1	0	1		1	1	1	1	0	1	1	TRUE								0
 * 182			0	1	1	0	1	1	0	1		1	0	1	1	0	1	1	TRUE								0
 * 183			1	1	1	0	1	1	0	1		0	0	1	1	0	1	1	TRUE								0
 * 184			0	0	0	1	1	1	0	1		0	0	1	0	0	1	1	TRUE								0
 * 185			1	0	0	1	1	1	0	1		1	0	1	0	0	1	1	TRUE								0
 * 186			0	1	0	1	1	1	0	1		1	1	1	0	0	1	1	TRUE								0
 * 187			1	1	0	1	1	1	0	1		0	1	1	0	0	1	1	TRUE								0
 * 188			0	0	1	1	1	1	0	1		0	1	0	0	0	1	1	TRUE								0
 * 189			1	0	1	1	1	1	0	1		1	1	0	0	0	1	1	TRUE								0
 * 190			0	1	1	1	1	1	0	1		1	0	0	0	0	1	1	TRUE								0
 * 191			1	1	1	1	1	1	0	1		0	0	0	0	0	1	1	FALSE								36
 * 192			0	0	0	0	0	0	1	1		0	0	0	0	0	1	0	FALSE								37
 * 193			1	0	0	0	0	0	1	1		1	0	0	0	0	1	0	FALSE								38
 * 194			0	1	0	0	0	0	1	1		1	1	0	0	0	1	0	TRUE								0
 * 195			1	1	0	0	0	0	1	1		0	1	0	0	0	1	0	FALSE								39
 * 196			0	0	1	0	0	0	1	1		0	1	1	0	0	1	0	TRUE								0
 * 197			1	0	1	0	0	0	1	1		1	1	1	0	0	1	0	TRUE								0
 * 198			0	1	1	0	0	0	1	1		1	0	1	0	0	1	0	TRUE								0
 * 199			1	1	1	0	0	0	1	1		0	0	1	0	0	1	0	FALSE								40
 * 200			0	0	0	1	0	0	1	1		0	0	1	1	0	1	0	TRUE								0
 * 201			1	0	0	1	0	0	1	1		1	0	1	1	0	1	0	TRUE								0
 * 202			0	1	0	1	0	0	1	1		1	1	1	1	0	1	0	TRUE								0
 * 203			1	1	0	1	0	0	1	1		0	1	1	1	0	1	0	TRUE								0
 * 204			0	0	1	1	0	0	1	1		0	1	0	1	0	1	0	TRUE								0
 * 205			1	0	1	1	0	0	1	1		1	1	0	1	0	1	0	TRUE								0
 * 206			0	1	1	1	0	0	1	1		1	0	0	1	0	1	0	TRUE								0
 * 207			1	1	1	1	0	0	1	1		0	0	0	1	0	1	0	FALSE								41
 * 208			0	0	0	0	1	0	1	1		0	0	0	1	1	1	0	TRUE								0
 * 209			1	0	0	0	1	0	1	1		1	0	0	1	1	1	0	TRUE								0
 * 210			0	1	0	0	1	0	1	1		1	1	0	1	1	1	0	TRUE								0
 * 211			1	1	0	0	1	0	1	1		0	1	0	1	1	1	0	TRUE								0
 * 212			0	0	1	0	1	0	1	1		0	1	1	1	1	1	0	TRUE								0
 * 213			1	0	1	0	1	0	1	1		1	1	1	1	1	1	0	TRUE								0
 * 214			0	1	1	0	1	0	1	1		1	0	1	1	1	1	0	TRUE								0
 * 215			1	1	1	0	1	0	1	1		0	0	1	1	1	1	0	TRUE								0
 * 216			0	0	0	1	1	0	1	1		0	0	1	0	1	1	0	TRUE								0
 * 217			1	0	0	1	1	0	1	1		1	0	1	0	1	1	0	TRUE								0
 * 218			0	1	0	1	1	0	1	1		1	1	1	0	1	1	0	TRUE								0
 * 219			1	1	0	1	1	0	1	1		0	1	1	0	1	1	0	TRUE								0
 * 220			0	0	1	1	1	0	1	1		0	1	0	0	1	1	0	TRUE								0
 * 221			1	0	1	1	1	0	1	1		1	1	0	0	1	1	0	TRUE								0
 * 222			0	1	1	1	1	0	1	1		1	0	0	0	1	1	0	TRUE								0
 * 223			1	1	1	1	1	0	1	1		0	0	0	0	1	1	0	FALSE								42
 * 224			0	0	0	0	0	1	1	1		0	0	0	0	1	0	0	FALSE								43
 * 225			1	0	0	0	0	1	1	1		1	0	0	0	1	0	0	FALSE								44
 * 226			0	1	0	0	0	1	1	1		1	1	0	0	1	0	0	TRUE								0
 * 227			1	1	0	0	0	1	1	1		0	1	0	0	1	0	0	FALSE								45
 * 228			0	0	1	0	0	1	1	1		0	1	1	0	1	0	0	TRUE								0
 * 229			1	0	1	0	0	1	1	1		1	1	1	0	1	0	0	TRUE								0
 * 230			0	1	1	0	0	1	1	1		1	0	1	0	1	0	0	TRUE								0
 * 231			1	1	1	0	0	1	1	1		0	0	1	0	1	0	0	FALSE								46
 * 232			0	0	0	1	0	1	1	1		0	0	1	1	1	0	0	TRUE								0
 * 233			1	0	0	1	0	1	1	1		1	0	1	1	1	0	0	TRUE								0
 * 234			0	1	0	1	0	1	1	1		1	1	1	1	1	0	0	TRUE								0
 * 235			1	1	0	1	0	1	1	1		0	1	1	1	1	0	0	TRUE								0
 * 236			0	0	1	1	0	1	1	1		0	1	0	1	1	0	0	TRUE								0
 * 237			1	0	1	1	0	1	1	1		1	1	0	1	1	0	0	TRUE								0
 * 238			0	1	1	1	0	1	1	1		1	0	0	1	1	0	0	TRUE								0
 * 239			1	1	1	1	0	1	1	1		0	0	0	1	1	0	0	FALSE								47
 * 240			0	0	0	0	1	1	1	1		0	0	0	1	0	0	0	FALSE								48
 * 241			1	0	0	0	1	1	1	1		1	0	0	1	0	0	0	FALSE								49
 * 242			0	1	0	0	1	1	1	1		1	1	0	1	0	0	0	TRUE								0
 * 243			1	1	0	0	1	1	1	1		0	1	0	1	0	0	0	FALSE								50
 * 244			0	0	1	0	1	1	1	1		0	1	1	1	0	0	0	TRUE								0
 * 245			1	0	1	0	1	1	1	1		1	1	1	1	0	0	0	TRUE								0
 * 246			0	1	1	0	1	1	1	1		1	0	1	1	0	0	0	TRUE								0
 * 247			1	1	1	0	1	1	1	1		0	0	1	1	0	0	0	FALSE								51
 * 248			0	0	0	1	1	1	1	1		0	0	1	0	0	0	0	FALSE								52
 * 249			1	0	0	1	1	1	1	1		1	0	1	0	0	0	0	FALSE								53
 * 250			0	1	0	1	1	1	1	1		1	1	1	0	0	0	0	TRUE								0
 * 251			1	1	0	1	1	1	1	1		0	1	1	0	0	0	0	FALSE								54
 * 252			0	0	1	1	1	1	1	1		0	1	0	0	0	0	0	FALSE								55
 * 253			1	0	1	1	1	1	1	1		1	1	0	0	0	0	0	FALSE								56
 * 254			0	1	1	1	1	1	1	1		1	0	0	0	0	0	0	FALSE								57
 * 255			1	1	1	1	1	1	1	1		0	0	0	0	0	0	0	FALSE								58
*/
