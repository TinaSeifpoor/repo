OPENCVPATH = "$$(OPENCV_ROOT)/build/include/"
INCLUDEPATH = $${OPENCVPATH}
win32-msvc2008 {
    ARC="x86"
    VC="vc9"
} else {
    win*:contains(QMAKE_TARGET.arch, x86_64):{
        ARC="x64"
        VC="vc10"
    } else {
        ARC="x86"
        VC="vc10"
    }
}
message(OpenCV $$(OPENCV_VER) 32-bit 2008: $$QMAKE_TARGET.arch)
message("OpenCV include path: $${OPENCVPATH}")


cvlibpath = "$$(OPENCV_ROOT)/build/$${ARC}/$${VC}/"

#message("$${cvlibpath}")
LIBS *= -L"$${cvlibpath}lib"
LIBS *= -L"$${cvlibpath}bin"

contains (OPENCV, all) {
    OPENCV-= all
    OPENCV*= calib3d contrib core features2d flann gpu highgui imgproc legacy ml nonfree objdetect ocl photo stitching superres ts video videostab
}

for(cvlib, OPENCV) {
    #message($$TARGET depends on $$cvlib)
    LIBS += -lopencv_$${cvlib}$$(OPENCV_VER)$${SUFFIX}
}
