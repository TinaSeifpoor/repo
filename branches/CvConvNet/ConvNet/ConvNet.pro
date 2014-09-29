#-------------------------------------------------
#
# Project created by QtCreator 2014-09-26T11:05:20
#
#-------------------------------------------------

CONFIG(debug, debug|release) {
    SUFFIX = d
    LIBS += -L../expat-2.1.0/win32/bin/Debug
} ELSE {
    LIBS += -L../expat-2.1.0/win32/bin/Release
}
INCLUDEPATH += include

TEMPLATE = lib
DEFINES += CONVNET_LIBRARY
CONFIG += opencv
OPENCV += 242d

INCLUDEPATH += ../expat-2.1.0/lib

LIBS += -lexpat

SOURCES +=  \
    src/cvconvnet.cpp \
    src/cvconvnetparser.cpp \
    src/cvconvolutionplane.cpp \
    src/cvfastsigmoid.cpp \
    src/cvgenericplane.cpp \
    src/cvmaxplane.cpp \
    src/cvrbfplane.cpp \
    src/cvsourceplane.cpp \
    src/cvsubsamplingplane.cpp

HEADERS += \
    include/cvconvnet.h \
    include/cvconvnetparser.h \
    include/cvconvolutionplane.h \
    include/cvfastsigmoid.h \
    include/cvgenericplane.h \
    include/cvmaxplane.h \
    include/cvrbfplane.h \
    include/cvsourceplane.h \
    include/cvsubsamplingplane.h \
    include/convnet_global.h

TARGET = CONVNET$$SUFFIX
DESTDIR = ../ConvNet/lib
