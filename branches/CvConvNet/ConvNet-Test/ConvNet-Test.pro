#-------------------------------------------------
#
# Project created by QtCreator 2014-09-27T09:32:19
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ConvNet-Test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG += opencv

CONFIG(debug, debug|release) {
    SUFFIX = d
    OPENCV += 242d
    LIBS += -L../expat-2.1.0/win32/bin/Debug
} ELSE {
    LIBS += -L../expat-2.1.0/win32/bin/Release
}

LIBS += -lexpat
LIBS += -L../ConvNet/lib/
LIBS += -lCONVNET$$SUFFIX

INCLUDEPATH += ../ConvNet/include

SOURCES += main.cpp
