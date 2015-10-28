#-------------------------------------------------
#
# Project created by QtCreator 2015-10-27T16:29:56
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = FaceWarper
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG += opencv

SOURCES += main.cpp \
    facewarpermodule.cpp

HEADERS += \
    facewarpermodule.h

DLIBPATH = D:/Downloads/dlib-18.17/dlib-18.17
INCLUDEPATH *= $${DLIBPATH}

LIBS *= -L"$${DLIBPATH}/lib/Debug"
LIBS *= -ldlib
