#-------------------------------------------------
#
# Project created by QtCreator 2014-12-19T09:36:49
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = TextToImage
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    downloadmanager.cpp \
    imagesourceparser.cpp \
    urlquerymanager.cpp

HEADERS += \
    downloadmanager.h \
    imagesourceparser.h \
    urlquerymanager.h
