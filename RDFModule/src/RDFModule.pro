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

SOURCES +=  rdfmodule.cpp \
            forest.cpp \
            tree.cpp \
            decisiontreetrainer.cpp \
            node.cpp

HEADERS +=  rdfmodule.h\
            rdfmodule_global.h \
            source.h \
            common.h \
            forest.h \
            tree.h \
            decisiontreetrainer.h \
            node.h

DESTDIR = ../lib

TARGET = rdfmodule$$SUFFIX
