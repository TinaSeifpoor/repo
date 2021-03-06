//#define EXAMPLE
#ifndef EXAMPLE
#include <QCoreApplication>
#include "cihanlib.h"
#include "opencv2/opencv.hpp"
#include <QDir>
using CihanLib::CData;
using CihanLib::CLandmark;
int main(int argc, char *argv[])
{
    QCoreApplication(argc, argv);
    cv::FileStorage storage(argv[1], cv::FileStorage::READ);
    cv::Mat goldenLandmarks;
    cv::read(storage["Golden"],goldenLandmarks);
    int goldenImageWidth, goldenImageHeight;
    storage["ImageWidth"] >> goldenImageWidth ;
    storage["ImageHeight"] >> goldenImageHeight ;

    for (int idxArg=2;idxArg<argc;idxArg+=2) {
        CData data(argv[idxArg]);
        QDir dest(argv[idxArg+1]);
        dest.mkpath(dest.path());
        foreach (QFileInfo fileInfo, data()) {
            CLandmark face(cv::imread(fileInfo.filePath().toStdString()));
            cv::Mat alignedImage = CLandmark::alignImage(cv::imread(fileInfo.filePath().toStdString()),goldenLandmarks);
            if (alignedImage.cols && alignedImage.rows) {
                cv::Mat croppedImage = cv::Mat(goldenImageHeight,goldenImageWidth,alignedImage.type());
                int croppableWidth = qMin(goldenImageWidth,alignedImage.cols);
                int croppableHeight= qMin(goldenImageHeight,alignedImage.rows);
                cv::Rect roi = cv::Rect(0,0,croppableWidth,croppableHeight);
                cv::Mat croppableImage = croppedImage(roi);
                cv::Mat alignedImageCroped = alignedImage(roi);
                alignedImageCroped.copyTo(croppableImage);
                cv::imwrite(dest.filePath(fileInfo.fileName()).toLatin1().constData(), croppedImage);
            }
        }
    }

    return 1;
}
#else
//
//  main.cpp
//  Procrustes
//
//  Created by Saburo Okita on 06/04/14.
//  Copyright (c) 2014 Saburo Okita. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "Procrustes.h"
#include <qmath.h>


using namespace std;
using namespace cv;

Mat convertLandmarks(Mat in) {

    Mat out = Mat(in.cols, 1, CV_32FC2);
    for (int i=0; i<in.cols; ++i) {
        Vec2f& elem = out.at<Vec2f>(i,0);
        elem[0] = in.at<float>(0,i);
        elem[1] = in.at<float>(1,i);
    }
    return out;

}

vector<Mat> generateTestData( int size ) {
    //    srand(static_cast<unsigned int>(time(NULL)));

    vector<Mat> result;

    /* First create random points X, centered at (250, 250) with stddev of 80 */
    //    Mat X(40, 1, CV_32FC2 );
    cv::FileStorage storage("D:/CihanRepo/AcademicRepositories/trunk/GenderRecognition/golden_landmarks.yaml", cv::FileStorage::READ);
    cv::Mat X;
    cv::read(storage["Golden"],X);
    X = convertLandmarks(X);
    RNG rng;
    rng.fill( X, RNG::NORMAL, Scalar( 250, 250 ), Scalar( 80, 80 ) );

    result.push_back( X );

    for( int i = 1; i < size; i++ ) {
        float scale = ((rand() % 100) + 25) / 100.0;
        Scalar translation( (rand() % 600) + 100, (rand() % 300) );

        /* Transform Y so that it's rotated and translated version of X */
        float angle = (rand() % 90) * 180.0 / M_PI;
        Mat S = (Mat_<float>(2,2) << cosf(angle), -sinf(angle), sinf(angle), cosf( angle) );
        Mat Y;
        cv::transform( scale * X, Y, S );
        Y += translation;

        /* Jitter the Y points a bit, so that it's not exactly transformed version of X */
        Mat jitter( Y.size(), Y.type() );
        rng.fill( jitter, RNG::NORMAL, Scalar(0, 0), Scalar( 5, 5 ));
        Y += jitter;

        result.push_back( Y );
    }



    return result;
}

/**
 * A simple helper class to plot the points
 **/
void plot(Mat& img, Mat& points, Scalar color ) {
    vector<Point2f> vec;
    points.copyTo( vec );

    for(vector<Point2f>::const_iterator it = vec.begin(); it!=vec.end(); ++it) {
        Point2f p = *it;
        circle( img, p, 2, color, 2 );
    }
}

void procrustesAnalysisTest() {
    namedWindow("");
    moveWindow( "", 0, 0 );

    vector<Mat> points = generateTestData( 2 );

    Mat img(600, 900, CV_8UC3, Scalar(255, 255, 255) );

    /* Plot X */
    plot( img, points[0], Scalar(0, 200, 0));

    /* Plot Y */
    plot( img, points[1], Scalar(200, 0, 0));

    imshow( "", img );
    waitKey();

    /*  Perform procrustes analysis, to obtain approximate transformed points from Y to X */
    Procrustes proc;
    proc.procrustes( points[0], points[1] );
    vector<Point2f> Y_prime = proc.yPrimeAsVector();
    for(vector<Point2f>::const_iterator it = Y_prime.begin(); it!=Y_prime.end(); ++it) {
        Point2f point = *it;
        circle( img, point, 3, Scalar(0, 0, 255), 2);
    }

    imshow( "", img );
    waitKey();

    /* Output the squared error, and scale, rotation and translation values involved in acquiring Y prime */
    cout << proc.error << endl;
    cout << proc.scale << endl;
    cout << proc.rotation << endl;
    cout << proc.translation << endl;
}

void generalizedProcrustesTest() {
    namedWindow("");
    moveWindow( "", 0, 0 );

    /* First we generate 6 set of points */
    vector<Mat> points = generateTestData( 6 );

    /* Colors to differentiate each set of points */
    vector<Scalar> colors;
    colors.push_back(Scalar( 255, 0, 0 ));
    colors.push_back(Scalar( 0, 255, 0 )   );
    colors.push_back(Scalar( 0, 0, 255 )   );
    colors.push_back(Scalar( 255, 255, 0 ) );
    colors.push_back(Scalar( 0, 255, 255 ) );
    colors.push_back(Scalar( 255, 0, 255 ) );

    /* Plot the points out */
    Mat img(600, 900, CV_8UC3, Scalar(255, 255, 255) );
    for( int i = 0; i < 6; i++ )
        plot( img, points[i], colors[i] );

    imshow( "", img );
    waitKey();

    /* Get a sub region of the original image, to plot our mean / canonical shape */
    Mat temp = Mat( img, Rect(580, 20, 300, 300) );
    temp     = Scalar( 220, 220, 220 );

    /* Apply general procrustes analysis to get the mean shape */
    Mat mean_mat;
    Procrustes proc;
    points = proc.generalizedProcrustes( points, mean_mat );

    /* The mean shape is normalized, thus in order to view it, we scale it and translate it a bit */
    vector<Point2f> mean_shape;
    mean_mat *= 600;
    mean_mat += Scalar( 150, 150 );
    mean_mat.reshape(2).copyTo( mean_shape );

    /* Plot out our image */
    for(vector<Point2f>::const_iterator it = mean_shape.begin(); it!=mean_shape.end(); ++it) {
        Point2f point = *it;
        circle( temp, point, 3, Scalar(0, 0, 255), 2);
    }

    imshow( "", img );
    waitKey();

}

int main(int argc, const char * argv[]) {
    procrustesAnalysisTest();

    return 0;
}
#endif
