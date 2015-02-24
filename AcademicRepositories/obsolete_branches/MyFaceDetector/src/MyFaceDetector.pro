#-------------------------------------------------
#
# Project created by QtCreator 2013-05-24T19:05:29
#
#-------------------------------------------------

QT       += core gui

TARGET = MyFaceDetector
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    MyDecisionForest.cpp \
    MyFeatureExtractor.cpp \
    MyHoughForest.cpp \
    MyBBEvaluator.cpp \
    imagewindow.cpp \
    MyFaceDetector.cpp \
    MyBaseLine.cpp \
    EvaluationListModel.cpp

HEADERS  += mainwindow.h \
    MyDecisionForest.h \
    MyFeatureExtractor.h \
    MyHoughForest.h \
    MyBBEvaluator.h \
    imagewindow.h \
    DecisionForestModel.h \
    FeatureExtractorModel.h \
    MyFaceDetector.h \
    MyBaseLine.h \
    EvaluationListModel.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib \
-lopencv_core \
-lopencv_imgproc \
-lopencv_highgui \
-lopencv_ml \
-lopencv_video \
-lopencv_features2d \
-lopencv_calib3d \
-lopencv_objdetect \
-lopencv_contrib \
-lopencv_legacy \
-lopencv_flann
