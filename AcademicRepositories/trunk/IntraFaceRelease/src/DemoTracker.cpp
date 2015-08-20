///////////////////////////////////////////////////////////////////////////////////////////////////////
/// DemoTracker.cpp
/// 
/// Description:
/// This program shows you how to use FaceAlignment class in tracking facial landmarks in a video or realtime. 
/// There are two modes: VIDEO, REALTIME.
/// In the VIDEO mode, the program reads input from a video and perform tracking.
/// In the REALTIME mode, the program reads input from the first camera it finds and perform tracking.
/// Note that tracking is performed on the largest face found. The face is detected through OpenCV.
/// In addition to the last version, we add head pose estimation.
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
#include <algorithm>
#include <string>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <intraface/FaceAlignment.h>
#include <intraface/XXDescriptor.h>

using namespace std;

bool compareRect(cv::Rect r1, cv::Rect r2) { return r1.height < r2.height; }

// 2 modes: REALTIME,VIDEO
#define VIDEO

void drawPose(cv::Mat& img, const cv::Mat& rot, float lineL)
{
	int loc[2] = {70, 70};
	int thickness = 2;
	int lineType  = 8;

	cv::Mat P = (cv::Mat_<float>(3,4) << 
		0, lineL, 0,  0,
		0, 0, -lineL, 0,
		0, 0, 0, -lineL);
	P = rot.rowRange(0,2)*P;
	P.row(0) += loc[0];
	P.row(1) += loc[1];
	cv::Point p0(P.at<float>(0,0),P.at<float>(1,0));

	line(img, p0, cv::Point(P.at<float>(0,1),P.at<float>(1,1)), cv::Scalar( 255, 0, 0 ), thickness, lineType);
	line(img, p0, cv::Point(P.at<float>(0,2),P.at<float>(1,2)), cv::Scalar( 0, 255, 0 ), thickness, lineType);
	line(img, p0, cv::Point(P.at<float>(0,3),P.at<float>(1,3)), cv::Scalar( 0, 0, 255 ), thickness, lineType);
}

int main()
{
	char detectionModel[] = "../models/DetectionModel-v1.5.bin";
	char trackingModel[]  = "../models/TrackingModel-v1.10.bin";
	string faceDetectionModel("../models/haarcascade_frontalface_alt2.xml");

	// initialize a XXDescriptor object
	INTRAFACE::XXDescriptor xxd(4);
	// initialize a FaceAlignment object
	INTRAFACE::FaceAlignment fa(detectionModel, trackingModel, &xxd);
	if (!fa.Initialized()) {
		cerr << "FaceAlignment cannot be initialized." << endl;
		return -1;
	}
	// load OpenCV face detector model
	cv::CascadeClassifier face_cascade;
	if( !face_cascade.load( faceDetectionModel ) )
	{ 
		cerr << "Error loading face detection model." << endl;
		return -1; 
	}
	

#ifdef REALTIME
	// use the first camera it finds
	cv::VideoCapture cap(0); 
#endif 

#ifdef VIDEO
	string filename("../data/vid.wmv");
	cv::VideoCapture cap(filename); 
#endif

	if(!cap.isOpened())  
		return -1;

	int key = 0;
	bool isDetect = true;
	bool eof = false;
	float score, notFace = 0.3;
	cv::Mat X,X0;
	string winname("Demo IntraFace Tracker");

	cv::namedWindow(winname);

	while (key!=27) // Press Esc to quit
	{
		cv::Mat frame;
		cap >> frame; // get a new frame from camera
		if (frame.rows == 0 || frame.cols == 0)
			break;

		if (isDetect)
		{
			// face detection
			vector<cv::Rect> faces;
			face_cascade.detectMultiScale(frame, faces, 1.2, 2, 0, cv::Size(50, 50));
			// if no face found, do nothing
			if (faces.empty()) {
				cv::imshow(winname,frame);
				key = cv::waitKey(5);
				continue ;
			}
			// facial feature detection on largest face found
			if (fa.Detect(frame,*max_element(faces.begin(),faces.end(),compareRect),X0,score) != INTRAFACE::IF_OK)
				break;
			isDetect = false;
		}
		else
		{
			// facial feature tracking
			if (fa.Track(frame,X0,X,score) != INTRAFACE::IF_OK)
				break;
			X0 = X;
		}
		if (score < notFace) // detected face is not reliable
			isDetect = true;
		else
		{
			// plot facial landmarks
			for (int i = 0 ; i < X0.cols ; i++)
				cv::circle(frame,cv::Point((int)X0.at<float>(0,i), (int)X0.at<float>(1,i)), 1, cv::Scalar(0,255,0), -1);
			// head pose estimation
			INTRAFACE::HeadPose hp;
			fa.EstimateHeadPose(X0,hp);
			// plot head pose
			drawPose(frame, hp.rot, 50);
		}
		cv::imshow(winname,frame);	
		key = cv::waitKey(5);
	}

	return 0;

}






