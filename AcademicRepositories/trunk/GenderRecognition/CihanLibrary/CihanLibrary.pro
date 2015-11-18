#-------------------------------------------------
#
# Project created by QtCreator 2015-11-11T10:01:28
#
#-------------------------------------------------

QT       -= gui

CONFIG(debug, debug|release) {
    SUFFIX = d
} else {
    SUFFIX =
}

TARGET = CihanLibrary$${SUFFIX}
TEMPLATE = lib

DEFINES += CIHANLIBRARY_LIBRARY

SOURCES += \
    procrustes.cpp \
    cihandata.cpp \
    cihanlandmark.cpp \
    histogram.cpp \
    lbp.cpp \
    cihanlbp.cpp \
    cihangoldenlandmark.cpp \
    cihancommon.cpp

HEADERS +=\
    asmopencv.h \
    procrustes.h \
    cihandata.h \
    cihan_global.h \
    cihanlandmark.h \
    cihanlib.h \
    histogram.hpp \
    lbp.hpp \
    cihanlbp.h \
    cihangoldenlandmark.h \
    cihancommon.h

CONFIG += opencv intraface

unix {
    target.path = /usr/lib
    INSTALLS += target
}


# Copies the given files to the destination directory
defineTest(copyHeader) {
    files = $$1

    DDIR = $$PWD/distribute/include/
    win32:DDIR ~= s,/,\\,g
    for(FILE, files) {

        # Replace slashes in paths with backslashes for Windows
        win32:FILE ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}



DESTDIR = $$PWD/distribute/lib
DLLDESTDIR = $$PWD/distribute/bin


copyHeader($$PWD/cihanlib.h $$PWD/cihandata.h $$PWD/cihanlandmark.h $$PWD/cihanlbp.h $$PWD/cihan_global.h $$PWD/cihancommon.h $$PWD/cihangoldenlandmark.h)
