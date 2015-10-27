#-------------------------------------------------
#
# Project created by QtCreator 2015-08-10T16:30:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FaceCropperBatch
TEMPLATE = app

# hack to add dlls to path
LIBS *= -L"D:/OpenCV/2.4.11/build/x64/vc10/bin"

CONFIG += opencv

SOURCES +=\
    facecropper.cpp \
    common.cpp \
    facecropperbatch.cpp \
    facelookuptable.cpp

HEADERS  += \
    facecropper.h \
    common.h \
    facecropperbatch.h \
    facelookuptable.h
