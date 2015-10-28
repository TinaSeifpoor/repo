#-------------------------------------------------
#
# Project created by QtCreator 2015-10-28T11:07:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG   += console

TARGET = FaceLandmarkPointAlignment
TEMPLATE = app

# hack to add dlls to path
LIBS *= -L"D:/OpenCV/2.4.11/build/x64/vc10/bin"

CONFIG+= opencv

SOURCES += main.cpp\
        mainwindow.cpp \
    tdfread.cpp

HEADERS  += mainwindow.h \
    tdfread.h

FORMS    += mainwindow.ui
