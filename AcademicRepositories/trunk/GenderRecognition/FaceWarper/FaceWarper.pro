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


INTRAFACEPATH = "../../IntraFaceRelease"

INCLUDEPATH += $${INTRAFACEPATH}/include
LIBS += -L"$${INTRAFACEPATH}/lib/Debug"
LIBS += -lIntraFaceDLLd

HEADERS += \
    extractlandmarks.h


INCLUDEPATH += "$${INTRAFACEPATH}/x64/Debug"
INCLUDEPATH += "D:\opencv\2.4.10\build\x64\vc10\bin"
