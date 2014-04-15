#-------------------------------------------------
#
# Project created by QtCreator 2014-03-09T19:49:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG(debug, debug|release) {
SUFFIX = d
}

TARGET = RDFTest
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG +=   opencv\
            rdfmodule

opencv += 2.4.5

SOURCES += main.cpp \
    imagecontainer.cpp \
    mainwindow.cpp \
    control.cpp \
    imagecontainerlist.cpp \
    imagewindow.cpp \
    featureextractor.cpp \
    browsesettingsdialog.cpp \
    imagelistwidget.cpp \
    instancelistwidget.cpp \
    classobject.cpp \
    imageobject.cpp \
    instanceobject.cpp \
    instanceextractor.cpp \
    classlistwidget.cpp


HEADERS += imagecontainer.h \
    mainwindow.h \
    control.h \
    imagecontainerlist.h \
    keypointextractor.h \
    common.h \
    imagewindow.h \
    featureextractor.h \
    browsesettingsdialog.h \
    classlistwidget.h \
    imagelistwidget.h \
    instancelistwidget.h \
    classobject.h \
    imageobject.h \
    instanceobject.h \
    instanceextractor.h

FORMS += \
    mainwindow.ui \
    browsesettingsdialog.ui
