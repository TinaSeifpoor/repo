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
    common.cpp \
    affiniteetemplate.cpp \
    minionselectionwidget.cpp \
    minionhub.cpp \
    quest.cpp \
    minion.cpp \
    questselectionwidget.cpp

HEADERS  += mainwindow.h \
    questhub.h \
    common.h \
    affiniteetemplate.h \
    minionselectionwidget.h \
    minionhub.h \
    quest.h \
    minion.h \
    questselectionwidget.h

FORMS    += mainwindow.ui
