################################################################
# intraface pri
################################################################

INTRAFACEPATH="../../IntraFaceRelease"
DEFINES += INTRAFACEPATH='\\"$${INTRAFACEPATH}\\"'

INCLUDEPATH += $${INTRAFACEPATH}/include
CONFIG(debug, debug|release) {
	LIBS += -L"$${INTRAFACEPATH}/lib/Debug"
	LIBS += -lIntraFaceDLLd
	LIBS += -L"$${INTRAFACEPATH}/x64/Debug"
 } else {
	LIBS += -L"$${INTRAFACEPATH}/lib/Release"
	LIBS += -lIntraFaceDLL
	LIBS += -L"$${INTRAFACEPATH}/x64/Release"
 }


message("IntraFace at $${INTRAFACEPATH} loaded")