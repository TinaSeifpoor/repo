#include "facewarpermodule.h"
#include "opencv2/opencv.hpp"

#include <vector>
using std::vector;

class FaceWarperModulePrivate
{
public:
    //Step 1: detect landmarks over the detected face
    vector<cv::Point2d> landmarks = landmark_detector->detectLandmarks(img_gray,Rect(r.x,r.y,r.width,r.height));
    //Step 2: align face
    Mat aligned_image;
    vector<cv::Point2d> aligned_landmarks;
    aligner->align(img_gray,aligned_image,landmarks,aligned_landmarks);
    //Step 3: normalize region
    Mat normalized_region = normalizer->process(aligned_image,Rect(r.x,r.y,r.width,r.height),aligned_landmarks);
    //Step 4: tan&&triggs
    normalized_region = ((FlandMarkFaceAlign *)normalizer)->tan_triggs_preprocessing(normalized_region, gamma_correct,dog,contrast_eq);
};


FaceWarperModule::FaceWarperModule():
    d(new FaceWarperModulePrivate())
{

}

