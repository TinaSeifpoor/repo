function [fftXA, fftXM, fftYA, fftYM, bw] = calcFD(reg, nHarmonics)
%CALCFD Summary of this function goes here
%   Detailed explanation goes here
nPoints = 5000;
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

%Get 5000 x samples
boundaryPointsSampled(:,1) = sample(boundaryPointsFixed(:,1),nPoints+1);
boundaryPointsSampled(:,2) = sample(boundaryPointsFixed(:,2),nPoints+1);

%fft for x
fftX = fft(boundaryPointsSampled(:,1));
fftXAngle = angle(fftX);
fftXMagni = abs(fftX);
%fft for y
fftY = fft(boundaryPointsSampled(:,2));
fftYAngle = angle(fftY);
fftYMagni = abs(fftY);

%% get first n harmonics
if (nHarmonics > 0)
    fftXAngle = fftXAngle(1:nHarmonics);
    fftXMagni = fftXMagni(1:nHarmonics);
    fftYAngle = fftYAngle(1:nHarmonics);
    fftYMagni = fftYMagni(1:nHarmonics);
end
fftXA = fftXAngle(2:end)';
fftXM = fftXMagni(2:end)';
fftYA = fftYAngle(2:end)';
fftYM = fftYMagni(2:end)';

%% get it back now
fftX = fftXMagni.*exp(1i*fftXAngle);

fftY = fftYMagni.*exp(1i*fftYAngle);

boundaryPointsRev(:,1) = abs(ifft(fftX));
boundaryPointsRev(:,2) = abs(ifft(fftY));

%Normalize points into 0:1 in x
xMin = min(boundaryPointsRev(:,1));
boundaryPointsRev(:,1)=boundaryPointsRev(:,1)-xMin;
xMax = max(boundaryPointsRev(:,1));
boundaryPointsRev(:,1)=boundaryPointsRev(:,1)./xMax;
%Normalize points into 0:1 in y
yMin = min(boundaryPointsRev(:,2));
boundaryPointsRev(:,2)=boundaryPointsRev(:,2)-yMin;
yMax = max(boundaryPointsRev(:,2));
boundaryPointsRev(:,2)=boundaryPointsRev(:,2)./yMax;



bw = poly2mask(boundaryPointsRev(:,1)*(nPoints)+1,...
    boundaryPointsRev(:,2)*(nPoints)+1, nPoints+1,nPoints+1);


end


function sampledValues = sample(unsampledValues, sampleCount)
idxBase = 1:size(unsampledValues);
pp = interp1(idxBase,unsampledValues,'cubic','pp');
idxDest = 1:size(unsampledValues)/sampleCount:size(unsampledValues);
sampledValues = ppval(pp,idxDest);
end