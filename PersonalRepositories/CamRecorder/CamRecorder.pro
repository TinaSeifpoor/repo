#-------------------------------------------------
#
# Project created by QtCreator 2015-04-08T20:22:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CamRecorder
TEMPLATE = app

CONFIG+=opencv
OPENCV+=all
include(opencv2411.pri)


SOURCES += main.cpp\
        mainwindow.cpp \
    cscamera.cpp \
    cscamerafolder.cpp \
    imagewidget.cpp \
    csimage.cpp \
    cvqtconversion.cpp

HEADERS  += mainwindow.h \
    cscamera.h \
    cscamera_p.h \
    cscamerafolder.h \
    cscamerafolder_p.h \
    imagewidget.h \
    csimage.h \
    cvqtconversion.h

FORMS    += mainwindow.ui

OTHER_FILES +=
