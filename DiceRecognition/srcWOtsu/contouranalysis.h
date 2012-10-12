#ifndef CONTOURANALYSIS_H
#define CONTOURANALYSIS_H

#include <opencv2/opencv.hpp>

typedef std::vector<cv::Point> ContourPoints;
typedef std::vector<ContourPoints> Contour;
typedef std::vector<Contour> ContourList;
typedef std::vector<cv::Vec4i> Hierarchy;
typedef std::vector<Hierarchy> HierarchyList;

class ContourAnalysis
{
public:
    ContourAnalysis();

    std::vector<int> area(Contour contours, Hierarchy hierarchy);
    std::vector<int> area(Contour contours);
    void showContours(Contour contours, Hierarchy hierarchy, cv::Size imSize, cv::Scalar color = cv::Scalar());
    void showContours(Contour contours, cv::Size imSize, cv::Scalar color = cv::Scalar());
    void drawContours_xld(Contour contours, Hierarchy hierarchy, cv::Mat im, cv::Scalar color);
    void selectContoursByArea(Contour contours, Hierarchy hierarchy, int minArea, int maxArea, Contour *contoursSelected, Hierarchy *hierarchySelected);
    void selectContoursByArea(Contour contours, int minArea, int maxArea, Contour *contoursSelected);
    void selectContours (Contour contours, Hierarchy hierarchy, std::vector<int> indices, Contour *contoursSelected, Hierarchy *hierarchySelected);
    void selectContours (Contour contours, std::vector<int> indices, Contour *contoursSelected);
    void selectContours (Contour contours, Hierarchy hierarchy, int index, Contour *contoursSelected, Hierarchy *hierarchySelected);
    void selectContours (Contour contours, int index, Contour *contoursSelected);
    void concatContours (Contour contours1, Hierarchy hierarchy1, Contour contours2, Hierarchy hierarchy2, Contour *contoursConcat, Hierarchy *hierarchyConcat);
    void concatContours (Contour contours1, Contour contours2, Contour *contoursConcat);
//    void reduceDomain (Contour contours, cv::Mat im, cv::Mat* imReduced);
    void intersectContours (Contour contours1, Hierarchy hierarchy1, Contour contours2, Hierarchy hierarchy2, cv::Size imSize, std::vector<Contour > *contoursConcat, std::vector<Hierarchy > *hierarchyConcat);
    void intersectContours (Contour contours1, Contour contours2, cv::Size imSize, std::vector<Contour > *contoursConcat);
    void selectContoursByCircularity (Contour contours, Hierarchy hierarchy, double minCircularity, double maxCircularity, Contour *contoursSelected, Hierarchy *hierarchySelected);
    void selectContoursByCircularity (Contour contours, double minCircularity, double maxCircularity, Contour *contoursSelected);
    void selectContoursByRectangularity (Contour contours, Hierarchy hierarchy, double minRectangularity, double maxRectangularity, Contour *contoursSelected, Hierarchy *hierarchySelected);
    void selectContoursByRectangularity (Contour contours, double minRectangularity, double maxRectangularity, Contour *contoursSelected);
    Hierarchy assignRandomHierarchy (Contour contours);
private:
    cv::Mat maskImageContour (Contour contours, cv::Size imSize);
    void sortContourHiearchy(Contour contours, Hierarchy hierarchy, std::vector<int> oldIndices, Contour *contoursSorted, Hierarchy *hierarchySorted);
    double calcCircularity(ContourPoints contourPoints);
    std::vector<double> calcCircularity(Contour contours);
    double calcRectangularity(ContourPoints contourPoints);
    std::vector<double> calcRectangularity(Contour contours);
};

#endif // CONTOURANALYSIS_H
