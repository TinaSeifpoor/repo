function [ bw ] = NormalizeSampleRegion( reg, nSamples )
%NORMALIZESAMPLEREGION Summary of this function goes here
%   Detailed explanation goes here

b = bwboundaries(reg, 'noholes');
boundaryPoints = b{1};
l = regionprops(reg,'Centroid');
pointC = l.Centroid;
boundaryPointsNorm = [boundaryPoints(:,1) - pointC(:,1),boundaryPoints(:,2) - pointC(:,2)];
ccdVector = (boundaryPointsNorm(:,1).^2 + boundaryPointsNorm(:,2).^2).^0.5;
[~, idx] = max(ccdVector);

boundaryPointsFixed = [boundaryPoints(1:idx-1,:);boundaryPoints(idx:end,:)];

%Normalize points into 0:1 in x
xMin = min(boundaryPointsFixed(:,1));
boundaryPointsFixed(:,1)=boundaryPointsFixed(:,1)-xMin;
xMax = max(boundaryPointsFixed(:,1));
boundaryPointsFixed(:,1)=boundaryPointsFixed(:,1)./xMax;
%Normalize points into 0:1 in y
yMin = min(boundaryPointsFixed(:,2));
boundaryPointsFixed(:,2)=boundaryPointsFixed(:,2)-yMin;
yMax = max(boundaryPointsFixed(:,2));
boundaryPointsFixed(:,2)=boundaryPointsFixed(:,2)./yMax;

%Get 1000 x samples
boundaryPointsSampled(:,1) = sampleThat(boundaryPointsFixed(:,1),nSamples);
boundaryPointsSampled(:,2) = sampleThat(boundaryPointsFixed(:,2),nSamples);
bw = poly2mask(boundaryPointsSampled(:,1)*(nSamples-1)+1,boundaryPointsSampled(:,2)*(nSamples-1)+1, nSamples,nSamples);
end


function sampledValues = sampleThat(unsampledValues, sampleCount)
idxBase = 1:size(unsampledValues);
pp = interp1(idxBase,unsampledValues,'cubic','pp');
idxDest = 1:size(unsampledValues)/sampleCount:size(unsampledValues);
sampledValues = ppval(pp,idxDest);
end
