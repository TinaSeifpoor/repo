#-------------------------------------------------
#
# Project created by QtCreator 2014-07-13T00:48:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MovingLine
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    ball.cpp \
    attack.cpp \
    swipeanimation.cpp \
    frametimer.cpp \
    animationfactory.cpp \
    maulanimation.cpp

HEADERS  += \
    mainwindow.h \
    ball.h \
    attack.h \
    swipeanimation.h \
    frametimer.h \
    animationfactory.h \
    maulanimation.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    res.qrc

OTHER_FILES +=
