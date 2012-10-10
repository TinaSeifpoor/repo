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

void ContourAnalysis::showContours(Contour contours, Hierarchy hierarchy, Size imSize, Scalar color)
{
    bool setRandomColor=color==Scalar();
    Mat dst = Mat::zeros(imSize, CV_8UC3);
    if( !contours.empty() && !hierarchy.empty() )
    {
        // iterate through all the top-level contours,
        // draw each connected component with its own random color
        int idx = 0;
        for( ; idx >= 0; idx = hierarchy[idx][0] )
        {
            if (setRandomColor)
                color = Scalar( (rand()&255), (rand()&255), (rand()&255) );
            cv::drawContours( dst, contours, idx, color, CV_FILLED, 8, hierarchy );
        }
    }
    imshow("Connected Components", dst);
}

void ContourAnalysis::drawContours_xld(Contour contours, Hierarchy hierarchy, Mat im, Scalar color)
{
    if( !contours.empty() && !hierarchy.empty() )
    {
        // iterate through all the top-level contours,
        // draw each connected component with its own random color
        int idx = 0;
        for( ; idx >= 0; idx = hierarchy[idx][0] )
        {
            if (color == Scalar())
                color = Scalar( (rand()&255), (rand()&255), (rand()&255) );
            cv::drawContours( im, contours, idx, color, CV_FILLED, 8, hierarchy );
        }
    }
}

void ContourAnalysis::selectContoursByArea(Contour contours, Hierarchy hierarchy, int minArea, int maxArea, Contour *contoursSelected, Hierarchy *hierarchySelected)
{
    if( !contours.empty() && !hierarchy.empty() )
    {
        Contour contoursUnsorted;
        Hierarchy hierarchyUnsorted;
        int idx = 0;
        Contour::iterator itContours = contoursUnsorted.begin();
        Hierarchy::iterator itHierarchies = hierarchyUnsorted.begin();
        vector<int> oldIndices;
        vector<int>::iterator itOldIndex = oldIndices.begin();
        //        int itHierarchies = -1;
        for(; idx >= 0; idx = hierarchy[idx][0])
        {
            int area = contourArea(contours[idx]);
            if (area>minArea && area < maxArea)
            {
                itContours = contoursUnsorted.insert(itContours, contours[idx]);
                itHierarchies = hierarchyUnsorted.insert(itHierarchies, hierarchy[idx]);
                itOldIndex = oldIndices.insert(itOldIndex, idx);
            }
        }
        // sort again hierarchies
        this->sortContourHiearchy(contoursUnsorted, hierarchyUnsorted, oldIndices, contoursSelected, hierarchySelected);
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

void ContourAnalysis::sortContourHiearchy(Contour contours, Hierarchy hierarchy, vector<int> oldIndices, Contour *contoursSorted, Hierarchy *hierarchySorted)
{
    // Assuming all contours are of the same level
    hierarchySorted->clear();
    contoursSorted->clear();
    Hierarchy::iterator itHierarchy = hierarchySorted->begin();
    Contour::iterator itContour = contoursSorted->begin();
    int nContours = contours.size();
    if( !contours.empty() && !hierarchy.empty() )
    {
        Scalar lastHier(-1, nContours-2, -1, -1);
        vector<Point> lastContour = contours[nContours-1];
        itContour = contoursSorted->insert(itContour, lastContour);

        itHierarchy = hierarchySorted->insert(itHierarchy, lastHier);
        for (int i=1; i < nContours-1; ++i)
        {
            Scalar currHier(nContours-i, nContours-i-2, -1, -1);
            vector<Point> currContour = contours[nContours-i-1];
            itHierarchy = hierarchySorted->insert(itHierarchy, currHier);
            itContour = contoursSorted->insert(itContour, currContour);
        }
        if (nContours>1)
        {
            Scalar firstHier(1, -1, -1, -1);
            vector<Point> firstContour = contours[0];
            itHierarchy = hierarchySorted->insert(itHierarchy, firstHier);
            itContour = contoursSorted->insert(itContour, firstContour);
        }
    }
}

void ContourAnalysis::selectContours(Contour contours, Hierarchy hierarchy, vector<int> indices, Contour *contoursSelected, Hierarchy *hierarchySelected)
{
    Contour contoursUnsorted(indices.size());
    Hierarchy hierarchyUnsorted(indices.size());
    vector<int> oldIndices(indices.size());
    int nContours = indices.size();
    for(int i=0; i<nContours; ++i)
    {
        contoursUnsorted[i] = contours[indices[i]];
        hierarchyUnsorted[i] = hierarchy[indices[i]];
        oldIndices[i] = i;
    }
    this->sortContourHiearchy(contoursUnsorted, hierarchyUnsorted, oldIndices, contoursSelected, hierarchySelected);
}

void ContourAnalysis::selectContours(Contour contours, vector<int> indices, Contour *contoursSelected)
{
    contoursSelected->clear();
    Contour::iterator it = contoursSelected->begin();
    int nContours = indices.size();
    contoursSelected->resize(nContours);
    for(int i=0; i<nContours; ++i)
    {
        it = contoursSelected->insert(it, contours[indices[i]]);
    }
}

void ContourAnalysis::selectContours(Contour contours, Hierarchy hierarchy, int index, Contour *contoursSelected, Hierarchy *hierarchySelected)
{
    vector<int> indices;
    indices.insert(indices.begin(), index);
    selectContours(contours, hierarchy, indices, contoursSelected, hierarchySelected);
}

void ContourAnalysis::selectContours(Contour contours, int index, Contour *contoursSelected)
{
    contoursSelected->clear();
    Contour::iterator it = contoursSelected->begin();
    contoursSelected->insert(it, contours[index]);
}

void ContourAnalysis::concatContours(Contour contours1, Hierarchy hierarchy1, Contour contours2, Hierarchy hierarchy2, Contour *contoursConcat, Hierarchy *hierarchyConcat)
{
    Contour contoursUnsorted;
    Hierarchy hierarchyUnsorted;

    Contour::iterator itContours = contoursUnsorted.begin();
    Hierarchy::iterator itHierarchies = hierarchyUnsorted.begin();
    //        int itHierarchies = -1;
    for(int i = 0; i < contours1.size(); ++i)
    {
        itContours = contoursUnsorted.insert(itContours, contours1[i]);
        itHierarchies = hierarchyUnsorted.insert(itHierarchies, hierarchy1[i]);
    }
    for(int i = 0; i < contours2.size(); ++i)
    {
        itContours = contoursUnsorted.insert(itContours, contours2[i]);
        itHierarchies = hierarchyUnsorted.insert(itHierarchies, hierarchy2[i]);
    }
    // sort again hierarchies
    this->sortContourHiearchy(contoursUnsorted, hierarchyUnsorted, std::vector<int>() , contoursConcat, hierarchyConcat);
}

//void ContourAnalysis::reduceDomain(Contour contours, Hierarchy hierarchy, Mat im, Mat* imOut)
//{
//    Mat imMask = maskImageContour(contours, im.size());
//    bitwise_and(im, imMask, *imOut);
//}

void ContourAnalysis::intersectContours(Contour contours1, Hierarchy hierarchy1, Contour contours2, Hierarchy hierarchy2, Size imSize, vector<Contour > *contoursIntersection, vector<Hierarchy > *hierarchyIntersection)
{
    vector<Contour >::iterator itContours = contoursIntersection->begin();
    vector<Hierarchy >::iterator itHierarchies = hierarchyIntersection->begin();
    int nContours1 = contours1.size();
    Mat imContour2 = this->maskImageContour(contours2, imSize);
    for (int i=0; i<nContours1; ++i)
    {
        Contour currContour1, intersectionContours;
        Hierarchy currHierarchy1, intersectionHierarchy;
        selectContours(contours1, hierarchy1, i, &currContour1, &currHierarchy1);
        Mat imContour1 = this->maskImageContour(currContour1, imSize);
        Mat imIntersection;
        bitwise_and(imContour1, imContour2, imIntersection);
        findContours(imIntersection, intersectionContours, intersectionHierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
        itContours = contoursIntersection->insert(itContours, intersectionContours);
        itHierarchies = hierarchyIntersection->insert(itHierarchies, intersectionHierarchy);
    }

}

void ContourAnalysis::selectContoursByCircularity(Contour contours, Hierarchy hierarchy, double minCircularity, double maxCircularity, Contour *contoursSelected, Hierarchy *hierarchySelected)
{
    Contour contoursUnsorted;
    Hierarchy hierarchyUnsorted;
    Contour::iterator itContours = contoursUnsorted.begin();
    Hierarchy::iterator itHierarchies = hierarchyUnsorted.begin();
    for(int i = 0; i < contours.size(); ++i)
    {
        vector<Point> contourPoints = contours[i];
        int area = contourArea(contourPoints);
        Moments m = moments(contours[i]);
        Point gravity;
        gravity.x = m.m10 / m.m00;
        gravity.y = m.m01 / m.m00;
        Scalar maxDistSquare=-1;
        for (int j=0; j< contourPoints.size(); ++j)
        {
            Point point = contourPoints[j];
            Scalar distSquare;
            cv::pow(Scalar(gravity.x - point.x, gravity.y - point.y),2,distSquare);
            if ((distSquare[0]+distSquare[1]) > maxDistSquare[0])
                maxDistSquare = distSquare[0]+distSquare[1];
        }
        double circularity = area / (maxDistSquare[0] * pi); //C = F / (max^2 * pi)
        if (circularity > minCircularity && circularity < maxCircularity)
        {
            itContours = contoursUnsorted.insert(itContours, contours[i]);
            itHierarchies = hierarchyUnsorted.insert(itHierarchies, hierarchy[i]);
        }
    }
    // sort again hierarchies
    this->sortContourHiearchy(contoursUnsorted, hierarchyUnsorted, std::vector<int>() , contoursSelected, hierarchySelected);
}

void ContourAnalysis::selectContoursByCircularity(Contour contours, double minCircularity, double maxCircularity, Contour *contoursSelected)
{
    contoursSelected->clear();
    Contour::iterator itContours = contoursSelected->begin();
    for(int i = 0; i < contours.size(); ++i)
    {
        vector<Point> contourPoints = contours[i];
        int area = contourArea(contourPoints);
        Moments m = moments(contours[i]);
        Point gravity;
        gravity.x = m.m10 / m.m00;
        gravity.y = m.m01 / m.m00;
        Scalar maxDistSquare=-1;
        for (int j=0; j< contourPoints.size(); ++j)
        {
            Point point = contourPoints[j];
            Scalar distSquare;
            cv::pow(Scalar(gravity.x - point.x, gravity.y - point.y),2,distSquare);
            if ((distSquare[0]+distSquare[1]) > maxDistSquare[0])
                maxDistSquare = distSquare[0]+distSquare[1];
        }
        double circularity = area / (maxDistSquare[0] * pi); //C = F / (max^2 * pi)
        if (circularity > minCircularity && circularity < maxCircularity)
        {
            itContours = contoursSelected->insert(itContours, contours[i]);
        }
    }
    // sort again hierarchies
}

void ContourAnalysis::selectContoursByRectangularity(Contour contours, Hierarchy hierarchy, double minRectangularity, double maxRectangularity, Contour *contoursSelected, Hierarchy *hierarchySelected)
{
    Contour contoursUnsorted;
    Hierarchy hierarchyUnsorted;
    Contour::iterator itContours = contoursUnsorted.begin();
    Hierarchy::iterator itHierarchies = hierarchyUnsorted.begin();
    for(int i = 0; i < contours.size(); ++i)
    {
        vector<Point> contourPoints = contours[i];
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
        double rectangularity = (double)area / rectArea;
        if (rectangularity > minRectangularity && rectangularity < maxRectangularity)
        {
            itContours = contoursUnsorted.insert(itContours, contours[i]);
            itHierarchies = hierarchyUnsorted.insert(itHierarchies, hierarchy[i]);
        }
    }
    // sort again hierarchies
    this->sortContourHiearchy(contoursUnsorted, hierarchyUnsorted, std::vector<int>() , contoursSelected, hierarchySelected);
}

void ContourAnalysis::selectContoursByRectangularity(Contour contours, double minRectangularity, double maxRectangularity, Contour *contoursSelected)
{
    contoursSelected->clear();
    Contour::iterator itContours = contoursSelected->begin();
    for(int i = 0; i < contours.size(); ++i)
    {
        vector<Point> contourPoints = contours[i];
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
        double rectangularity = (double)area / rectArea;
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
