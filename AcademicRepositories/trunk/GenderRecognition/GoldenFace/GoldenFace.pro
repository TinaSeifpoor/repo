#-------------------------------------------------
#
# Project created by QtCreator 2015-11-11T08:55:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GoldenFace

TEMPLATE = app

CONFIG += opencv

LIBS *= -L"D:/OpenCV/2.4.11/build/x64/vc10/bin"

SOURCES += main.cpp

RESOURCES += \
    resources.qrc

HEADERS += \
    asmopencv.h
