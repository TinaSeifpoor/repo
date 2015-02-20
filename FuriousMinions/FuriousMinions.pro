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
    questselectionwidget.cpp \
    reward.cpp \
    questprogresshub.cpp \
    questprogresswidget.cpp \
    synchronizedtimer.cpp \
    verticalscrollarea.cpp \
    globalvariables.cpp \
    furiouspushbutton.cpp \
    miniondata.cpp

HEADERS  += mainwindow.h \
    questhub.h \
    common.h \
    affiniteetemplate.h \
    minionselectionwidget.h \
    minionhub.h \
    quest.h \
    minion.h \
    questselectionwidget.h \
    reward.h \
    questprogresshub.h \
    questprogresswidget.h \
    synchronizedtimer.h \
    verticalscrollarea.h \
    globalvariables.h \
    furiouspushbutton.h \
    miniondata.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
