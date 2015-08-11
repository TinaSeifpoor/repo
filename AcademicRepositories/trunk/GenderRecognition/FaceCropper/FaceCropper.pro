#-------------------------------------------------
#
# Project created by QtCreator 2015-08-10T16:30:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FaceCropper
TEMPLATE = app

# hack to add dlls to path
LIBS *= -L"D:/OpenCV/2.4.11/build/x64/vc10/bin"

CONFIG += opencv

SOURCES += main.cpp\
        mainwindow.cpp \
    facecropper.cpp \
    common.cpp \
    imagedisplayer.cpp \
    imagescrollarea.cpp

HEADERS  += mainwindow.h \
    facecropper.h \
    common.h \
    imagedisplayer.h \
    imagescrollarea.h

FORMS    += mainwindow.ui \
    imagedisplayer.ui

RESOURCES +=

