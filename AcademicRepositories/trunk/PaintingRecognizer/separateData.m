function [XTrain, XTest, yTrain, yTest] = separateData(varargin)
%SEPARATEDATA Summary of this function goes here
%   Detailed explanation goes here
all_X = varargin{1};
all_y = varargin{2};
trainF = varargin{3};
idxPerm = randperm(numel(all_y));
if (trainF>1)
    nTrain = trainF;
elseif (trainF>0)
    nTrain = floor(numel(all_y)*trainF);
end
idxTrain = idxPerm(1:nTrain);
idxTest = idxPerm(nTrain+1:end);
XTrain = all_X(idxTrain,:);
yTrain = all_y(idxTrain);
XTest = all_X(idxTest,:);
yTest = all_y(idxTest);
end

