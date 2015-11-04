#-------------------------------------------------
#
# Project created by QtCreator 2015-11-03T15:33:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GenericSorter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageresultviewer.cpp \
    visionitem.cpp \
    imagemover.cpp

HEADERS  += mainwindow.h \
    imageresultviewer.h \
    visionitem.h \
    imagemover.h

FORMS    += mainwindow.ui
