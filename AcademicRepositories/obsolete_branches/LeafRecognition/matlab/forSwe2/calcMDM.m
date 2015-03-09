function [regPointsBMDM,regPointsAMDM,regPointsMMDM]= calcMDM(reg,k)
%CALCMDM Summary of this function goes here
%   Detailed explanation goes here
reg = pickHighestAreaRegion(reg);
b = bwboundaries(reg, 'noholes');
regPoints = b{1};
regPointsX = regPoints(:,1); regPointsY = regPoints(:,2);
[regPointsYS, regPointsXS] = ...
    downscaleVectorSize(k,regPointsX,regPointsY);

regD = poly2mask(regPointsXS, regPointsYS, size(reg,1), size(reg,2));


regPointsXForX = repmat(regPointsXS,1,size(regPointsXS));
regPointsYForY = repmat(regPointsYS,1,size(regPointsYS));

regPointsD = sqrt((regPointsXForX - regPointsXForX').^2+...
    (regPointsYForY-regPointsYForY').^2);

% Rotate columns so that first element becomes zeros
regPointsDM = regPointsD;
for idxCol = 1:size(regPointsDM,1)
    colS = regPointsDM(:,idxCol);
    colR = [colS(idxCol:end); colS(1:idxCol-1)];
    regPointsDM(:,idxCol) = colR;
end
% Sort each row ascendently
regPointsDMS= sort(regPointsDM,2);
% Remove its first and the last [(n-1)/2] rows to construct a new matrix
regPointsBMDM = regPointsDMS;
regPointsBMDM(end-floor((size(regPointsBMDM,1)-1)/2):end,:) = [];
regPointsBMDM(1,:) = [];
regPointsAMDM = regPointsBMDM/mean(regPointsBMDM(:));
regPointsMMDM = regPointsBMDM/max(regPointsBMDM(:));
end

