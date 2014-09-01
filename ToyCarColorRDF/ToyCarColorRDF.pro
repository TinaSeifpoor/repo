#-------------------------------------------------
#
# Project created by QtCreator 2014-09-01T20:51:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += ../RDFModule/include

CONFIG(debug, debug|release) {
SUFFIX = d
}

TARGET = ToyCarColorRDF$$SUFFIX

LIBS += -L../RDFModule/lib
LIBS += -lrdfmodule$$SUFFIX

CONFIG += opencv
OPENCV += 242d
SOURCES += main.cpp\
        mainwindow.cpp \
    initializer.cpp \
    imagecolorfeatures.cpp \
    imagecolorfeature.cpp

HEADERS  += mainwindow.h \
    initializer.h \
    imagecolorfeatures.h \
    imagecolorfeature.h

FORMS    += mainwindow.ui
