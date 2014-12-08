#-------------------------------------------------
#
# Project created by QtCreator 2014-12-08T19:57:38
#
#-------------------------------------------------

QT       -= core gui

TARGET = vl_nnconv
TEMPLATE = lib

DEFINES += MATLAB_MEX_FILE
TARGET_EXT = mex
MATLABROOT = "D:/Program Files/MATLAB/R2014a/extern/"

INCLUDEPATH += $${MATLABROOT}include

LIBS += -L$${MATLABROOT}lib/win64/microsoft
LIBS += -llibmex -llibmx -llibmat -llibmwblas

DEF_FILE = configure.def

message($${MATLABROOT})


SOURCES += \
    bits/im2col.cpp \
    bits/normalize.cpp \
    bits/pooling.cpp \
    bits/subsample.cpp \
    vl_imreadjpeg.c

HEADERS +=\
        mexfilebuilder_global.h \
    bits/gpu.hpp \
    bits/im2col.hpp \
    bits/mexutils.h \
    bits/nnhelper.h \
    bits/normalize.hpp \
    bits/pooling.hpp \
    bits/subsample.hpp

OTHER_FILES += \
    configure.def
