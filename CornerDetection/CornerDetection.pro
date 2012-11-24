TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    visionmanager.cpp \
    harriscornerdetector.cpp \
    measureinterestpointdetectors.cpp

INCLUDEPATH += E:/OpenCV2.4.2/OpenCV/build/include/

LIBS += -L"E:/opencv2.4.2/OpenCV/build/x86/vc9/lib/"

LIBS +=  -lopencv_calib3d242d\
            -lopencv_contrib242d\
            -lopencv_core242d\
            -lopencv_features2d242d\
            -lopencv_flann242d\
            -lopencv_gpu242d\
            -lopencv_haartraining_engined\
            -lopencv_highgui242d\
            -lopencv_imgproc242d\
            -lopencv_legacy242d\
            -lopencv_ml242d\
            -lopencv_nonfree242d\
            -lopencv_objdetect242d\
            -lopencv_photo242d\
            -lopencv_stitching242d\
            -lopencv_ts242d\
            -lopencv_video242d\
            -lopencv_videostab242d

HEADERS += \
    visionmanager.h \
    harriscornerdetector.h \
    measureinterestpointdetectors.h
