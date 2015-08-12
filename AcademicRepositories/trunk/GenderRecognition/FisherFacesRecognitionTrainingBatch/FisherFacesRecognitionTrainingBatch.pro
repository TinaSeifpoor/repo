#-------------------------------------------------
#
# Project created by QtCreator 2015-08-12T12:13:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FisherFacesRecognitionTrainingBatch
TEMPLATE = app

# hack to add dlls to path
LIBS *= -L"D:/OpenCV/2.4.11/build/x64/vc10/bin"

CONFIG += opencv

SOURCES += \
    fisherfacesrecognitiontrainingbatch.cpp \
    common.cpp \
    fisherfacerecognizer.cpp

HEADERS  += \
    fisherfacesrecognitiontrainingbatch.h \
    common.h \
    fisherfacerecognizer.h
