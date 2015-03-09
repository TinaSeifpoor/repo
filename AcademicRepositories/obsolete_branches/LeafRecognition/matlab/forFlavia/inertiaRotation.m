function [ tR ] = inertiaRotation( reg )
%INERTIAROTATION Summary of this function goes here
%   Detailed explanation goes here
% [yList, xList] = find(bwmorph(reg, 'thin',Inf));
% L = regionprops(reg,'ConvexHull');
% L = L.ConvexHull;
% regC=poly2mask(L(:,1),L(:,2), size(reg,1),size(reg,2));
% figure;imshow(regC);
[yList, xList] = find(reg);
points = [xList,yList];
% xListN = xList - pointC(1);
% yListN = yList - pointC(2);
% pointsS(:,1)=smooth(points(:,1));
% pointsS(:,2)=smooth(points(:,2));
pA = princomp(points);
% R(3,3)=1;
% tR = maketform('affine', R);

tR = rad2deg(atan2(pA(2),pA(1)));
% C = sum(pointListN*pointListN');
% 
% sumX = sum(xListN); sumY = sum(yListN); sumXY= sumX*sumY;
% sumX2 = sum(xListN.^2); sumY2 = sum(yListN.^2);
% 
% I = [sumX2, -sumXY;...
%     -sumXY,  sumY2];
% [R,E,~] = svd(I);
% R(3,3) = 1;
% T1 = eye(3); T2 = eye(3);
% T1([3,6]) = -pointC;
% T2([3,6]) = pointC;
% H = T1*R^-1*T2;
% tR = maketform('affine', H);
%% Get rid of sign ambiguity
% [tR, newPoints] = removeSignAmbiguity(T1,R^-1,T2,[xList,yList], pointC);
% newReg = false(size(reg));
% newReg(sub2ind(size(reg),int32(newPoints))) = true;
end

function [tR, newPoints]=removeSignAmbiguity(T1,R,T2,points, pointC)
H = T1*R*T2;
tR = maketform('affine', H);
[newPoints]=tformfwd(tR,points);
xLimitMean = mean([max(newPoints(1,:)),min(newPoints(1,:))]);
yLimitMean = mean([max(newPoints(2,:)),min(newPoints(2,:))]);
HChanged = false;
dispPoints(newPoints);
if ((xLimitMean > pointC(1)) && (yLimitMean > pointC(2)))
    R2 = eye(3);
    R2([1,2,4,5]) = [cosd(180),sind(180),-sind(180),cosd(180)];
    R = R2*R;
    HChanged = true;
elseif ((xLimitMean < pointC(1)) && (yLimitMean > pointC(2)))
    R2 = eye(3);
    R2([1,2,4,5]) = [cosd(90),sind(90),-sind(90),cosd(90)];
    R = R2*R;
    HChanged = true;
elseif ((xLimitMean > pointC(1)) && (yLimitMean < pointC(2)))
    R2 = eye(3);
    R2([1,2,4,5]) = [cosd(-90),sind(-90),-sind(-90),cosd(-90)];
    R = R2*R;
    HChanged = true;
end
if (HChanged)
    H = T1*R*T2;
    tR = maketform('affine', H);
    [newPoints]=tformfwd(tR,points);
end
dispPoints(newPoints);
end

function [] = dispPoints (points)
points = int32(points);
xMax = max(points(:,1));
yMax = max(points(:,2));
reg = false(xMax,yMax);
reg(sub2ind(size(reg),points(:,1),points(:,2))) = true;
figure;imshow(reg);
end