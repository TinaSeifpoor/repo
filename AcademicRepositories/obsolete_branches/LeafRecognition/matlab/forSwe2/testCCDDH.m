clear;clc;close all;
datasetPath = '../Dataset/flavia/';
dataset = parseDataset(datasetPath);
idxClass = 5;
idxInstance = 5;
class = dataset{idxClass};
filename = class{idxInstance};
filename = filename(1:numel(filename)-4);
imInstance = imread(class{idxInstance});
regLeaf = segmentLeaf(imInstance);

nSteps = 20;

boundaryPoints = bwboundaries(regLeaf);
boundaryPoints = boundaryPoints{1};
l = regionprops(regLeaf,'Centroid');
pointC = l.Centroid;
boundaryPointsNorm = [boundaryPoints(:,1) - pointC(:,1),boundaryPoints(:,2) - pointC(:,2)];
ccdVector = (boundaryPointsNorm(:,1).^2 + boundaryPointsNorm(:,2).^2).^0.5;
ccdDiffVector = ccdVector(1:size(ccdVector,1)-1,:) - ccdVector(2:size(ccdVector,1),:);
[maxDist, idx] = max(ccdDiffVector);
% maxCCDPoint = boundaryPoints(idx,:);
[minDist, idx] = min(ccdDiffVector);
% minCCDPoint = boundaryPoints(idx,:);
ccddh = hist(ccdDiffVector,nSteps)./numel(ccdDiffVector);
