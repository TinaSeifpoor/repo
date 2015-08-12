#-------------------------------------------------
#
# Project created by QtCreator 2015-08-12T09:54:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FisherFacesRecognitionTraining
TEMPLATE = app

# hack to add dlls to path
LIBS *= -L"D:/OpenCV/2.4.11/build/x64/vc10/bin"

CONFIG += opencv

SOURCES += main.cpp\
        mainwindow.cpp \
    common.cpp \
    fisherfacerecognizer.cpp \
    imagedroplabel.cpp

HEADERS  += mainwindow.h \
    common.h \
    fisherfacerecognizer.h \
    imagedroplabel.h

FORMS    += mainwindow.ui
