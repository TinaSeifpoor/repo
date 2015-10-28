#-------------------------------------------------
#
# Project created by QtCreator 2015-10-27T17:21:21
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = IntrafaceTests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG += opencv

SOURCES += \
    DemoDetector.cpp

HEADERS += \


INTRAFACEPATH = "../../IntraFaceRelease"

INCLUDEPATH += $${INTRAFACEPATH}/include
LIBS += -L"$${INTRAFACEPATH}/lib/Debug"
INCLUDEPATH += "$${INTRAFACEPATH}/x64/Debug"
LIBS += -lIntraFaceDLLd
