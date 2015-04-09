INCLUDEPATH = "$${OPENCVROOT}build/include/"
message("OpenCV include path: $${OPENCVROOT}build/include/")
win32-msvc2008 {
    message(OpenCV $${ver} 32-bit 2008: $$QMAKE_TARGET.arch)
    cvlibpath = "$${OPENCVROOT}build/x86/vc10/"
} else {
    win*:contains(QMAKE_TARGET.arch, x86_64):{
        cvlibpath = "$${OPENCVROOT}build/x64/vc10/"
        message(OpenCV $${ver} 64-bit 2010: $$QMAKE_TARGET.arch)
    } else {
        message(OpenCV $${ver} 32-bit 2010: $$QMAKE_TARGET.arch)
        cvlibpath = "$${OPENCVROOT}build/x86/vc10/"
    }
}

message("$${cvlibpath}")
LIBS *= -L"$${cvlibpath}lib"
LIBS *= -L"$${cvlibpath}bin"

contains (OPENCV, all) {
    OPENCV-= all
    OPENCV*= calib3d contrib core features2d flann gpu highgui imgproc legacy ml nonfree objdetect ocl photo stitching superres ts video videostab
}

for(cvlib, OPENCV) {
    #message($$TARGET depends on $$cvlib)
    LIBS += -lopencv_$${cvlib}$${ver}$${SUFFIX}
}
