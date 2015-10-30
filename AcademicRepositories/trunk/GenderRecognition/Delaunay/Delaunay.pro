#-------------------------------------------------
#
# Project created by QtCreator 2015-10-30T11:44:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Delaunay
TEMPLATE = app

CONFIG += opencv

SOURCES +=\
        mainwindow.cpp \
    delaunay2.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
