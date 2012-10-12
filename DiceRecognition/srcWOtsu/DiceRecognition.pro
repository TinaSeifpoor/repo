#-------------------------------------------------
#
# Project created by QtCreator 2012-10-06T05:25:17
#
#-------------------------------------------------

QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DiceRecognition
TEMPLATE = app

INCLUDEPATH += D:/opencv/2.4.2/OpenCV/build/include/

LIBS += -L"D:/opencv/2.4.2/OpenCV/build/x86/vc9/lib/"

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

















SOURCES += \
    RandomDiceRecognizer.cpp \
    PerformanceMeter.cpp \
    main.cpp \
    dicerecognizer.cpp \
    contouranalysis.cpp

HEADERS  += \
    Util.h \
    RandomDiceRecognizer.h \
    PerformanceMeter.h \
    dicerecognizer.h \
    IDiceRecongizer.h \
    contouranalysis.h
