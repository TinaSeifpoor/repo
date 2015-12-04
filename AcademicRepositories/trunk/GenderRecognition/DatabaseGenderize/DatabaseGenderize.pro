#-------------------------------------------------
#
# Project created by QtCreator 2015-11-03T12:01:07
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = DatabaseGenderize
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


CONFIG += cihanlib

SOURCES += main.cpp \
    genderizerdata.cpp \
    splitdata.cpp

HEADERS += \
    genderizerdata.h \
    splitdata.h
