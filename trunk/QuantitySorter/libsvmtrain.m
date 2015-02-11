function model = libsvmtrain(X,y)
%LIBSVMTRAIN Summary of this function goes here
%   Detailed explanation goes here

model.minX = min(min(X));
model.maxX = max(max(X));
X_norm = (X-model.minX) / ((model.maxX-model.minX) / 2) - 1;
model.m = svmtrain(y,double(X_norm), '-b 1 -t 0 -q');
end

