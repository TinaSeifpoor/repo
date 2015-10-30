#-------------------------------------------------
#
# Project created by QtCreator 2015-10-29T10:05:55
#
#-------------------------------------------------

QT       += core gui

TARGET = FaceWarper
CONFIG   += console

TEMPLATE = app

CONFIG += opencv

SOURCES += main.cpp \
    extractlandmarks.cpp


INTRAFACEPATH="../../IntraFaceRelease"
DEFINES += INTRAFACEPATH='\\"$${INTRAFACEPATH}\\"'

INCLUDEPATH += $${INTRAFACEPATH}/include
LIBS += -L"$${INTRAFACEPATH}/lib/Debug"
LIBS += -lIntraFaceDLLd

HEADERS += \
    extractlandmarks.h

LIBS *= -L"D:/OpenCV/2.4.11/build/x64/vc10/bin"
LIBS += -L"$${INTRAFACEPATH}/x64/Debug"
