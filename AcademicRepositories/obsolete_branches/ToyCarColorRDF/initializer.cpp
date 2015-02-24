#include "initializer.h"
#include "source.h"
#include <QFileInfo>
#include <QDir>
#include "opencv2/opencv.hpp"
#include "imagecolorfeature.h"
#include <QHash>

QHash<ImageColorFeature::ColorChannel, QList<int> > colorHistogram(cv::Mat image);
Source* Initializer::getSource() {
    QDir imgDir("../toy_car_lear/imstdsize");
    QStringList classNameList = imgDir.entryList(QDir::NoDotAndDotDot | QDir::Dirs);
    QList<Sample> samples;
    foreach (QString className, classNameList) {
        QDir classDir(imgDir);
        classDir.cd(className);
        QFileInfoList imageFileInfoList = classDir.entryInfoList(QStringList()<<"*.png", QDir::Files);
        foreach (QFileInfo imageFileInfo, imageFileInfoList) {
            QHash<ImageColorFeature::ColorChannel, QList<int> > feature =  colorHistogram(cv::imread(imageFileInfo.filePath().toStdString()));
            Sample s;
            s.sampleClass = classDir.dirName().toInt();
            s.sampleId = imageFileInfo.fileName();
            s.sampleSource = QVariant::fromValue<QHash<ImageColorFeature::ColorChannel, QList<int> > >(feature);
            samples << s;
        }
    }
    return new Source(samples);
}

QHash<ImageColorFeature::ColorChannel, QList<int> > colorHistogram(cv::Mat image) {
    using namespace cv;
    using namespace std;
    /// Establish the number of bins
    QHash<ImageColorFeature::ColorChannel, QList<int> > res;
    {
        /// Separate the image in 3 places ( B, G and R )
        vector<Mat> bgr_planes;
        split( image, bgr_planes );


        /// Set the ranges ( for B,G,R) )
        float range[] = { 0, 256 } ;
        const float* histRange = { range };

        bool uniform = true; bool accumulate = false;

        Mat b_hist, g_hist, r_hist;

        /// Compute the histograms:
        calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &binSize, &histRange, uniform, accumulate );
        calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &binSize, &histRange, uniform, accumulate );
        calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &binSize, &histRange, uniform, accumulate );

        // Draw the histograms for B, G and R
        int hist_w = 512; int hist_h = 400;

        Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );


        normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
        normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
        normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
        QList<int> r,g,b;
        for (int i =0; i<binSize; ++i) {
            b << b_hist.at<float>(i);
            g << g_hist.at<float>(i);
            r << r_hist.at<float>(i);
        }
        res.insert(ImageColorFeature::Red, r);
        res.insert(ImageColorFeature::Green, g);
        res.insert(ImageColorFeature::Blue, b);
    }
    {
        Mat hsvImage;
        cvtColor(image, hsvImage, COLOR_BGR2HSV_FULL);
        /// Separate the image in 3 places ( B, G and R )
        vector<Mat> bgr_planes;
        split( image, bgr_planes );

        /// Set the ranges ( for B,G,R) )
        float range[] = { 0, 256 } ;
        const float* histRange = { range };

        bool uniform = true; bool accumulate = false;

        Mat b_hist, g_hist, r_hist;

        /// Compute the histograms:
        calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &binSize, &histRange, uniform, accumulate );
        calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &binSize, &histRange, uniform, accumulate );
        calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &binSize, &histRange, uniform, accumulate );

        // Draw the histograms for B, G and R
        int hist_w = 512; int hist_h = 400;

        Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );


        normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
        normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
        normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
        QList<int> r,g,b;
        for (int i =0; i<binSize; ++i) {
            b << b_hist.at<float>(i);
            g << g_hist.at<float>(i);
            r << r_hist.at<float>(i);
        }
        res.insert(ImageColorFeature::Hue, r);
        res.insert(ImageColorFeature::Saturation, g);
        res.insert(ImageColorFeature::Value, b);

    }

    return res;
}
