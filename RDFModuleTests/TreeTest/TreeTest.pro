#-------------------------------------------------
#
# Project created by QtCreator 2014-08-19T16:15:14
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = TreeTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../RDFModule/src

CONFIG(debug, debug|release) {
SUFFIX = d
}

LIBS += -LD:\Projects\RDF\RDFModule\lib
LIBS += -lrdfmodule$$SUFFIX

SOURCES += main.cpp \
    featuretest.cpp \
    featurestest.cpp \
    initializer.cpp \

HEADERS += featuretest.h \
    featurestest.h \
    initializer.h
