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

CONFIG +=   opencv

opencv += 2.4.5

SOURCES += main.cpp \
    mainwindow.cpp \
    imagewindow.cpp \
    browsesettingsdialog.cpp \
    imagelistwidget.cpp \
    instancelistwidget.cpp \
    classobject.cpp \
    imageobject.cpp \
    instanceobject.cpp \
    classlistwidget.cpp \
    filesystembrowser.cpp \
    xml.cpp \
    common.cpp


HEADERS += \
    mainwindow.h \
    common.h \
    imagewindow.h \
    browsesettingsdialog.h \
    classlistwidget.h \
    imagelistwidget.h \
    instancelistwidget.h \
    classobject.h \
    imageobject.h \
    instanceobject.h \
    filesystembrowser.h \
    xml.h

FORMS += \
    mainwindow.ui \
    browsesettingsdialog.ui \
    filesystembrowser.ui
