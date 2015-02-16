#-------------------------------------------------
#
# Project created by QtCreator 2015-02-16T11:44:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FuriousMinions
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    questhub.cpp \
    questwidget.cpp \
    common.cpp \
    miniontemplate.cpp \
    affiniteetemplate.cpp \
    minionselectionwidget.cpp

HEADERS  += mainwindow.h \
    questhub.h \
    questwidget.h \
    common.h \
    miniontemplate.h \
    affiniteetemplate.h \
    minionselectionwidget.h

FORMS    += mainwindow.ui
