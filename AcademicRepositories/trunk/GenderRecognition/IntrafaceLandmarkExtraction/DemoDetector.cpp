///////////////////////////////////////////////////////////////////////////////////////////////////////
/// DemoDetector.cpp
/// 
/// Description:
/// This program shows you how to use FaceAlignment class in detecting facial landmarks on one image. 
/// In this version, head pose estimation is added and see DemoTracker for a demo.
///
/// There are two modes: INTERACTIVE, AUTO.
///
/// In the INTERACTIVE mode, the user is asked to create a draggable rectangle to locate one's face. 
/// To obtain good performance, the upper and lower boundaries need to exceed one's eyebrow and lip. 
/// For examples of good input rectangles, please refer to "../data/good_input_rect.jpg".
///
/// In the AUTO mode, the faces are found through OpenCV face detector.
///
/// Note that the initialization is optimized for OpenCV face detector. However, the algorithm is not
/// very sensitive to initialization. It is possible to replace OpenCV's with your own face detector. 
/// If the output of your face detector largely differs from the OpenCV's, you can add a constant offset
/// to the output of your detector using an optional parameter in the constructor of FaceAlignment.
/// See more details in "FaceAlignment.h".
///
/// Dependencies: None. OpenCV DLLs and include folders are copied.
///
/// Author: Xuehan Xiong, xiong828@gmail.com
///
/// Creation Date: 1/25/2014
///
/// Version: 1.2
///
/// Citation: 
/// Xuehan Xiong, Fernando de la Torre, Supervised Descent Method and Its Application to Face Alignment. CVPR, 2013
///////////////////////////////////////////////////////////////////////////////////////////////////////



#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <intraface/FaceAlignment.h>
#include <intraface/XXDescriptor.h>

#include <QDir>
#include <QFileInfo>

using namespace std;


// 2 modes: AUTO, INTERACTIVE
#define AUTO

int main(int argc, char** argv)
{
    char detectionModel[] = "../models/DetectionModel-v1.5.bin";
    char trackingModel[] = "../models/TrackingModel-v1.10.bin";
    INTRAFACE::XXDescriptor xxd(4);

    INTRAFACE::FaceAlignment*fa = new INTRAFACE::FaceAlignment(detectionModel, trackingModel, &xxd);

    if (!fa->Initialized()) {
        cerr << "FaceAlignment cannot be initialized." << endl;
        return -1;
    }

    QDir sourceDir(argv[1]);
    QFileInfoList files = sourceDir.entryInfoList(QStringList() << "*.jpg" << "*.jpeg", QDir::Files);
    QDir imageOutputDir(argv[2]);
    if (!imageOutputDir.exists())
        imageOutputDir.mkpath(imageOutputDir.path());
    QDir landmarkOutputDir(argv[3]);
    if (!landmarkOutputDir.exists())
        landmarkOutputDir.mkpath(landmarkOutputDir.path());
    float score, notFace = 0.5;
    cv::Mat firstLandmarks;
    for (int i=0; i<files.count(); ++i) {
        QFileInfo sourceFile = files.value(i);
        cv::Mat frame = cv::imread(sourceFile.filePath().toStdString());
        cv::Rect frameRect = cv::Rect(0,0,frame.cols,frame.rows);
        cv::Mat landmarks;
        cv::Mat alignedFrame = frame.clone();
        if (fa->Detect(frame,frameRect,landmarks,score) == INTRAFACE::IF_OK)
        {
            if (firstLandmarks.cols==0)
                firstLandmarks = landmarks;
            // only draw valid faces
            if (score >= notFace) {
                for (int i = 0 ; i < landmarks.cols ; i++)
                    cv::circle(frame,cv::Point((int)landmarks.at<float>(0,i), (int)landmarks.at<float>(1,i)), 1, cv::Scalar(0,255,0), -1);
            }
        }
        float res = fa->Align(alignedFrame, firstLandmarks);
        cv::imwrite(imageOutputDir.filePath(sourceFile.fileName()).toStdString(), frame);
        cv::imwrite(imageOutputDir.filePath(sourceFile.fileName()).toStdString(), frame);
        cv::write(cv::FileStorage(landmarkOutputDir.filePath(sourceFile.baseName()).append(".txt").toStdString(),cv::FileStorage::WRITE),landmarks);
    }

    delete fa;

    return 0;

}

