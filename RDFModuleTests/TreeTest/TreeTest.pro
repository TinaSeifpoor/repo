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


SOURCES += main.cpp \
    ../../RDFModule/src/node.cpp \
    featuretest.cpp \
    ../../RDFModule/src/features.cpp \
    featurestest.cpp \
    ../../RDFModule/src/source.cpp \
    initializer.cpp \
    ../../RDFModule/src/forest.cpp \
    ../../RDFModule/src/foresttrainer.cpp

HEADERS += \
    ../../RDFModule/src/source.h \
    ../../RDFModule/src/node.h \
    ../../RDFModule/src/vectorindexsorter.h \
    featuretest.h \
    ../../RDFModule/src/listrandomsorter.h \
    ../../RDFModule/src/feature.h \
    ../../RDFModule/src/features.h \
    featurestest.h \
    initializer.h \
    ../../RDFModule/src/forest.h \
    ../../RDFModule/src/foresttrainer.h
