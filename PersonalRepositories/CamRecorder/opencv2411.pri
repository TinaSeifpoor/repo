OPENCVROOT = "d:/OpenCV/2.4.11/"
ver = "2411"
CONFIG(debug, debug|release) {
    SUFFIX = d
} else {
    SUFFIX =
}
include(opencv.pri)

