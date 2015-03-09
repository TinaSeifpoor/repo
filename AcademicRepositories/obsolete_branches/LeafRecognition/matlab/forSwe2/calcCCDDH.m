function [ ccddh ] = calcCCDDH( reg, nSteps )
%CALCCCDDH Summary of this function goes here
%   Detailed explanation goes here

%% Smooth it!!
%% Smooth it!!

boundaryPoints = bwboundaries(reg);
boundaryPoints = boundaryPoints{1};
l = regionprops(reg,'Centroid');
pointC = l.Centroid;
boundaryPointsNorm = [boundaryPoints(:,1) - pointC(:,1),boundaryPoints(:,2) - pointC(:,2)];
ccdVector = (boundaryPointsNorm(:,1).^2 + boundaryPointsNorm(:,2).^2).^0.5;
ccdDiffVector = ccdVector(1:size(ccdVector,1)-1,:) - ccdVector(2:size(ccdVector,1),:);
ccddh = hist(ccdDiffVector,nSteps)./numel(ccdDiffVector);

end

