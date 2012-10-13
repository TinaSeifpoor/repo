#include "contouranalysis.h"
using namespace cv;
using namespace std;
static const double pi = 3.14159265358979323846;
ContourAnalysis::ContourAnalysis()
{}

vector<int> ContourAnalysis::area(Contour contours, Hierarchy hierarchy)
{
    vector<int> areaList;
    if( !contours.empty() && !hierarchy.empty() )
    {
        int idx = 0;
        vector<int>::iterator it;

        it = areaList.begin();
        for( ; idx >= 0; idx = hierarchy[idx][0])
        {
            int area = contourArea(contours[idx]);
            it = areaList.insert(it, area);
        }
    }
    return areaList;
}

void ContourAnalysis::drawContours_xld(Contour contours, Mat im, Scalar color)
{
    if( !contours.empty() )
    {
        int idx = 0;
        Hierarchy hierarchy = this->assignRandomHierarchy(contours);
        if (color == Scalar())
            color = Scalar( (rand()&255), (rand()&255), (rand()&255) );
        for( ; idx >= 0; idx = hierarchy[idx][0] )
        {
            cv::drawContours( im, contours, idx, color, CV_FILLED, 8, hierarchy );
        }
    }
}

void ContourAnalysis::selectContoursByArea(Contour contours, int minArea, int maxArea, Contour *contoursSelected)
{
    contoursSelected->clear();
    if( !contours.empty())
    {
        Contour::iterator itContours = contoursSelected->begin();
        int nContourPoints = contours.size();
        for (int i=0; i<nContourPoints; ++i)
        {
            int area = contourArea(contours[i]);
            if (area>minArea && area < maxArea)
            {
                itContours = contoursSelected->insert(itContours, contours[i]);
            }
        }
    }
}

double ContourAnalysis::calcCircularity(ContourPoints contourPoints)
{
    Point2f center;
    float radius;
    minEnclosingCircle(contourPoints, center, radius);
    int circleArea = (double)(radius*radius)*pi;
    int area = contourArea(contourPoints);
    return (double)area / circleArea;
}

vector<double> ContourAnalysis::calcCircularity(Contour contours)
{
    int nContours = contours.size();
    vector<double> circularityList(nContours);
    for (int i=0; i< nContours; ++i)
        circularityList[i] = this->calcCircularity(contours[i]);
    return circularityList;
}

double ContourAnalysis::calcRectangularity(ContourPoints contourPoints)
{
    Point2f pts[4];
    minAreaRect(contourPoints).points(pts);
    vector<Point> rectanglePoints;
    rectanglePoints.reserve(4);
    vector<Point>::iterator itRectanglePoints=rectanglePoints.begin();
    for (int i = 0; i<4; ++i)
    {
        itRectanglePoints = rectanglePoints.insert(itRectanglePoints, pts[i]);
    }
    int rectArea = contourArea(rectanglePoints);
    int area = contourArea(contourPoints);
    return (double)(area / rectArea);
}

vector<double> ContourAnalysis::calcRectangularity(Contour contours)
{
    int nContours = contours.size();
    vector<double> rectangularityList(nContours);
    for (int i=0; i< nContours; ++i)
        rectangularityList[i] = this->calcRectangularity(contours[i]);
    return rectangularityList;
}

void ContourAnalysis::selectContours(Contour contours, vector<int> indices, Contour *contoursSelected)
{
    contoursSelected->clear();
    Contour::iterator it = contoursSelected->begin();
    int nContours = indices.size();
    for(int i=0; i<nContours; ++i)
    {
        it = contoursSelected->insert(it, contours[indices[i]]);
    }
}

void ContourAnalysis::selectContours(Contour contours, int index, Contour *contoursSelected)
{
    contoursSelected->clear();
    Contour::iterator it = contoursSelected->begin();
    contoursSelected->insert(it, contours[index]);
}

void ContourAnalysis::selectContoursByCircularity(Contour contours, double minCircularity, double maxCircularity, Contour *contoursSelected)
{
    contoursSelected->clear();
    Contour::iterator itContours = contoursSelected->begin();
    for(int i = 0; i < contours.size(); ++i)
    {
        double circularity = this->calcCircularity(contours[i]);
        if (circularity > minCircularity && circularity < maxCircularity)
        {
            itContours = contoursSelected->insert(itContours, contours[i]);
        }
    }
}

void ContourAnalysis::selectContoursByRectangularity(Contour contours, double minRectangularity, double maxRectangularity, Contour *contoursSelected)
{
    contoursSelected->clear();
    Contour::iterator itContours = contoursSelected->begin();
    for(int i = 0; i < contours.size(); ++i)
    {
        double rectangularity = this->calcRectangularity(contours[i]);
        if (rectangularity > minRectangularity && rectangularity < maxRectangularity)
        {
            itContours = contoursSelected->insert(itContours, contours[i]);
        }
    }
    // sort again hierarchies
}

Hierarchy ContourAnalysis::assignRandomHierarchy(Contour contours)
{
    Hierarchy hierarchy;
    Hierarchy::iterator itHierarchy = hierarchy.begin();
    int nContours = contours.size();
    if( !contours.empty())
    {
        Scalar lastHier(-1, nContours-2, -1, -1);
        itHierarchy = hierarchy.insert(itHierarchy, lastHier);
        for (int i=1; i < nContours-1; ++i)
        {
            Scalar currHier(nContours-i, nContours-i-2, -1, -1);
            itHierarchy = hierarchy.insert(itHierarchy, currHier);
        }
        if (nContours>1)
        {
            Scalar firstHier(1, -1, -1, -1);
            itHierarchy = hierarchy.insert(itHierarchy, firstHier);
        }
    }
    return hierarchy;
}

Mat ContourAnalysis::maskImageContour(Contour contours, Size imSize)
{
    int nContours = contours.size();
    Mat imMask;
    imMask = Mat::zeros(imSize, 0);
    for (int i=0; i<nContours; ++i)
    {
        vector<Point> pointsSelected = contours[i];
        fillConvexPoly(imMask, pointsSelected, Scalar(255),8,0);
    }
    return imMask;
}


void ContourAnalysis::showContours(Contour contours, Size imSize, Scalar color)
{
    bool setRandomColor=color==Scalar();
    Mat imDisp = Mat::zeros(imSize, CV_8UC3);
    if( !contours.empty())
    {
        // iterate through all the top-level contours,
        // draw each connected component with its own random color
        Hierarchy hierarchy = this->assignRandomHierarchy(contours);
        int idx = 0;
        for( ; idx >= 0; idx = hierarchy[idx][0] )
        {
            if (setRandomColor)
                color = Scalar( (rand()&255), (rand()&255), (rand()&255) );
            cv::drawContours( imDisp, contours, idx, color, CV_FILLED, 8, hierarchy );
        }
    }
    imshow("Connected Components", imDisp);
}
