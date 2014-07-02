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
    featuretest.cpp \
    ../../RDFModule/src/features.cpp \
    featurestest.cpp \
    ../../RDFModule/src/source.cpp

HEADERS += \
    ../../RDFModule/src/source.h \
    ../../RDFModule/src/node.h \
    ../../RDFModule/src/vectorindexsorter.h \
    featuretest.h \
    ../../RDFModule/src/listrandomsorter.h \
    ../../RDFModule/src/feature.h \
    ../../RDFModule/src/features.h \
    featurestest.h
