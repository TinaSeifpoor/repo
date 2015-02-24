#-------------------------------------------------
#
# Project created by QtCreator 2014-02-15T11:05:20
#
#-------------------------------------------------

QT       -= gui

TEMPLATE =  lib

CONFIG(debug, debug|release) {
SUFFIX = d
}

DEFINES +=  RDFMODULE_LIBRARY

SOURCES +=  \
            forest.cpp \
            node.cpp \
    features.cpp \
    source.cpp \
    common.cpp

HEADERS += \
            rdfmodule_global.h \
            source.h \
            common.h \
            forest.h \
            node.h \
    vectorindexsorter.h \
    features.h \
    feature.h \
    listrandomsorter.h

DESTDIR = ../lib

TARGET = rdfmodule$$SUFFIX
