#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T16:58:01
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ExtractLandmarksTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG += opencv


SOURCES += main.cpp \
    extractlandmarks.cpp \
    splitdata.cpp

HEADERS += \
    extractlandmarks.h \
    splitdata.h

INTRAFACEPATH="../../IntraFaceRelease"
DEFINES += INTRAFACEPATH='\\"$${INTRAFACEPATH}\\"'

INCLUDEPATH += $${INTRAFACEPATH}/include
LIBS += -L"$${INTRAFACEPATH}/lib/Debug"
LIBS += -lIntraFaceDLLd

HEADERS += \
    extractlandmarks.h

LIBS *= -L"D:/OpenCV/2.4.11/build/x64/vc10/bin"
LIBS += -L"$${INTRAFACEPATH}/x64/Debug"
