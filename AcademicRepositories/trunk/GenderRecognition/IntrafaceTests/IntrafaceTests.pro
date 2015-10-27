#-------------------------------------------------
#
# Project created by QtCreator 2015-10-27T17:21:21
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = IntrafaceTests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG += opencv

SOURCES += \
    binary_model_file.cpp \
    DemoDetector.cpp

HEADERS += \
    intraface/binary_model_file.h \
    intraface/FaceAlignment.h \
    intraface/Marcos.h \
    intraface/XXDescriptor.h

INTRAFACEPATH = "D:\CihanRepo\AcademicRepositories\trunk\IntraFaceRelease"

INCLUDEPATH += $${INTRAFACEPATH}/include
LIBS += -L"$${INTRAFACEPATH}/lib/Debug"
INCLUDEPATH += "$${INTRAFACEPATH}/x64/Debug"
LIBS += -lIntraFaceDLLd
