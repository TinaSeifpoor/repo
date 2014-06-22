#-------------------------------------------------
#
# Project created by QtCreator 2014-06-19T00:59:41
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = NodeTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../../RDFModule/src/node.cpp \
    sourcetest.cpp \
    featurestest.cpp \
    featuretest.cpp \
    ../../RDFModule/src/features.cpp

HEADERS += \
    ../../RDFModule/src/source.h \
    ../../RDFModule/src/node.h \
    sourcetest.h \
    ../../RDFModule/src/vectorindexsorter.h \
    featurestest.h \
    featuretest.h \
    ../../RDFModule/src/listrandomsorter.h \
    ../../RDFModule/src/feature.h
