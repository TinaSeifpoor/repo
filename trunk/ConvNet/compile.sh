#!/bin/sh

SRC_ROOT=`pwd`

# Build root is specified by first commandline parameter
if [ $# -ne 1 ]
then
    BUILD_ROOT="/var/tmp/conv-net-0.1-prealpha_buildroot/"
else
    BUILD_ROOT=$1
fi

if [ ! -d $BUILD_ROOT ]
then
    mkdir -p $BUILD_ROOT
fi

echo Building conv-net library
cd $BUILD_ROOT

cmake $SRC_ROOT  # For a DEBUG version
# cmake -D CMAKE_BUILD_TYPE=Release $SRC_ROOT # For a RELEASE version
make

# Copy binaries
mkdir -p ./usr/local/lib/
mkdir -p ./usr/local/bin/
mkdir -p ./usr/local/include/
cp libcvconvnet.a ./usr/local/lib/
cp $SRC_ROOT/include/cvconvnet.h ./usr/local/include/
cp testimg ./usr/local/bin/
cp testmnist ./usr/local/bin/


# Copy sources
mkdir -p ./usr/local/share/conv-net/
cp -r $SRC_ROOT/* ./usr/local/share/conv-net/

rm -r CMakeFiles/*
rmdir CMakeFiles
ls -I usr | xargs rm

#echo Building documentation
#cd SRC_ROOT/doc/
#doxygen cvconvnet.dox





