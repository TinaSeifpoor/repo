close all;clear;clc;
MATLABROOT = 'D:/Program Files/MATLAB/R2014a/extern/';
LIBSPATH = '-LD:/Program Files/MATLAB/R2014a/extern/lib/win64/microsoft';
LIBS = '-llibmex -llibmx -llibmat -llibmwblas -llibeng';

sources = {'bits/im2col.cpp';'bits/normalize.cpp    bits/pooling.cpp  bits/subsample.cpp'};
headers =  'bits/gpu.hpp    bits/im2col.hpp    bits/mexutils.h,    bits/nnhelper.h,    bits/normalize.hpp    bits/pooling.hpp    bits/subsample.hpp';


mex('vl_nnconv.cpp','bits/im2col.cpp','bits/normalize.cpp','bits/pooling.cpp','bits/subsample.cpp',...
    LIBSPATH, '-llibmex', '-llibmx', '-llibmat', '-llibmwblas', '-llibeng');
mex('vl_nnnormalize.cpp','bits/im2col.cpp','bits/normalize.cpp','bits/pooling.cpp','bits/subsample.cpp',...
    LIBSPATH, '-llibmex', '-llibmx', '-llibmat', '-llibmwblas', '-llibeng');
mex('vl_nnpool.cpp','bits/im2col.cpp','bits/normalize.cpp','bits/pooling.cpp','bits/subsample.cpp',...
    LIBSPATH, '-llibmex', '-llibmx', '-llibmat', '-llibmwblas', '-llibeng');