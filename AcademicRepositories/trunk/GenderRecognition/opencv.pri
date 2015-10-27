################################################################
# halcon pri
################################################################
CONFIG(debug, debug|release) {
    SUFFIX = d
 } else {
    SUFFIX =
 }

INCLUDEPATH *= "D:/OpenCV/2.4.11/build/include"
LIBS *= -L"D:/OpenCV/2.4.11/build/x64/vc10/lib"

LIBS *= \
-lopencv_calib3d2411$${SUFFIX}\
-lopencv_contrib2411$${SUFFIX}\
-lopencv_core2411$${SUFFIX}\
-lopencv_features2d2411$${SUFFIX}\
-lopencv_flann2411$${SUFFIX}\
-lopencv_gpu2411$${SUFFIX}\
-lopencv_highgui2411$${SUFFIX}\
-lopencv_imgproc2411$${SUFFIX}\
-lopencv_legacy2411$${SUFFIX}\
-lopencv_ml2411$${SUFFIX}\
-lopencv_nonfree2411$${SUFFIX}\
-lopencv_objdetect2411$${SUFFIX}\
-lopencv_ocl2411$${SUFFIX}\
-lopencv_photo2411$${SUFFIX}\
-lopencv_stitching2411$${SUFFIX}\
-lopencv_superres2411$${SUFFIX}\
-lopencv_ts2411$${SUFFIX}\
-lopencv_video2411$${SUFFIX}\
-lopencv_videostab2411$${SUFFIX}

message("OpenCV loaded: $${SUFFIX}")