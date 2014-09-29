PROJECT (CvConvolutionalNet)

# IF() ENDIF() statements
SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)

# Specify build-type as Debug if not specified already
IF (NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE Debug)
ENDIF ()

# Produce verbose makefiles
# SET(CMAKE_VERBOSE_MAKEFILE ON)

# Sources for library
SET(CVCONVNET_SRCS
	src/cvsubsamplingplane.cpp
	src/cvconvolutionplane.cpp
	src/cvgenericplane.cpp
	src/cvsourceplane.cpp
	src/cvrbfplane.cpp
	src/cvmaxplane.cpp
	src/cvconvnetparser.cpp
	src/cvfastsigmoid.cpp
	src/cvconvnet.cpp
)

# Sources for test files
SET(TESTIMG_SRCS tst/testimg.cpp)
SET(TESTMNIST_SRCS tst/testmnist.cpp)

# Here are common paths (in addition to default paths)
SET (INCLUDE_SEARCH_PATH
	/usr/local/include /usr/include /usr/local/include/opencv/
	/usr/include/opencv/ c:/program\ files/opencv/include D:/opencv2.4.5/build/include
)

SET (LIBRARY_SEARCH_PATH
	/usr/local/lib /usr/lib d:/program\ files/opencv/lib c:/windows/system32 D:\opencv2.4.5\build\include\opencv2 D:/opencv2.4.5-bin/bin
)

# Find OpenCV and Expat
FIND_PATH(CV_H NAMES cv.h PATHS ${INCLUDE_SEARCH_PATH} )
FIND_PATH(HIGHGUI_H NAMES highgui.h PATHS ${INCLUDE_SEARCH_PATH} )
FIND_PATH(EXPAT_H NAMES expat.h	PATHS ${INCLUDE_SEARCH_PATH} )

FIND_LIBRARY(LIBCV NAMES cv PATHS ${LIBRARY_SEARCH_PATH} )
FIND_LIBRARY(LIBHIGHGUI NAMES highgui PATHS ${LIBRARY_SEARCH_PATH} )
FIND_LIBRARY(LIBEXPAT NAMES expat PATHS ${LIBRARY_SEARCH_PATH} )

INCLUDE_DIRECTORIES(include/ ${CV_H} ${HIGHGUI_H} ${EXPAT_H})

# Here is out library
ADD_LIBRARY(cvconvnet STATIC ${CVCONVNET_SRCS})

# Here are our test programs
ADD_EXECUTABLE(testimg ${TESTIMG_SRCS})
ADD_EXECUTABLE(testmnist ${TESTMNIST_SRCS})

# Compiler options are different for Release and Debug
IF (CMAKE_BUILD_TYPE MATCHES Release)
	# Highly optimized + cancel all assert()s
	ADD_DEFINITIONS(-O3 -DNDEBUG) 
ELSE ()
	# Include debug info, profiling info, some text output
	ADD_DEFINITIONS(-O -pg -g -DDEBUG)
	# Set profiling for linker too
	SET_TARGET_PROPERTIES(testmnist PROPERTIES LINK_FLAGS "-pg")
ENDIF ()

# We should link our test programs to libraries
TARGET_LINK_LIBRARIES(testimg cvconvnet ${LIBCV} ${LIBHIGHGUI} ${LIBEXPAT})
TARGET_LINK_LIBRARIES(testmnist cvconvnet ${LIBCV} ${LIBHIGHGUI} ${LIBEXPAT})

