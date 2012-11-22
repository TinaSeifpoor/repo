#ifndef CONTOURANALYSIS_H
#define CONTOURANALYSIS_H

#include <opencv2/opencv.hpp>

typedef std::vector<cv::Point> ContourPoints;
typedef std::vector<ContourPoints> Contour;
typedef std::vector<Contour> ContourList;
typedef std::vector<cv::Vec4i> Hierarchy;
typedef std::vector<Hierarchy> HierarchyList;
typedef cv::Mat Im;

class ContourAnalysis
{
public:
    ContourAnalysis();

    std::vector<int> area(Contour contours, Hierarchy hierarchy);
    std::vector<int> area(Contour contours);
    void showContours(Contour contours, cv::Size imSize, cv::Scalar color = cv::Scalar());
    void drawContours_xld(Contour contours, cv::Mat im, cv::Scalar color);
    void selectContoursByArea(Contour contours, int minArea, int maxArea, Contour *contoursSelected);
    void selectContours (Contour contours, std::vector<int> indices, Contour *contoursSelected);
    void selectContours (Contour contours, int index, Contour *contoursSelected);
    void concatContours (Contour contours1, Contour contours2, Contour *contoursConcat);
    void intersectContours (Contour contours1, Contour contours2, cv::Size imSize, std::vector<Contour > *contoursConcat);
    void selectContoursByCircularity (Contour contours, double minCircularity, double maxCircularity, Contour *contoursSelected);
    void selectContoursByRectangularity (Contour contours, double minRectangularity, double maxRectangularity, Contour *contoursSelected);
    Hierarchy assignRandomHierarchy (Contour contours);
    double calcCircularity(ContourPoints contourPoints);
    std::vector<double> calcCircularity(Contour contours);
    double calcRectangularity(ContourPoints contourPoints);
    std::vector<double> calcRectangularity(Contour contours);
    double calcAspectRatio(ContourPoints contourPoints);
    std::vector<double> calcAspectRatio(Contour contours);
private:
    cv::Mat maskImageContour (Contour contours, cv::Size imSize);
};

#endif // CONTOURANALYSIS_H
