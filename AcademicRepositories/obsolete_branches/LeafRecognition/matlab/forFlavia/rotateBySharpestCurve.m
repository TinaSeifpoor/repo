function [ tR ] = rotateBySharpestCurve( reg )
%INERTIAROTATION Summary of this function goes here
%   Detailed explanation goes here

[~, maxCCDPoint,pointC] = calcCCD(reg);
phi = calcLineAngle(pointC, maxCCDPoint);
R = eye(3);
R([1,2,4,5]) = [cos(phi),sin(phi),-sin(phi),cos(phi)];
T1 = eye(3); T2 = eye(3);
T1([3,6]) = -pointC;
T2([3,6]) = pointC;
H = T1*R*T2;
tR = maketform('affine', H);
figure;imshow(reg);hold on;plot([maxCCDPoint(2),pointC(2)],[maxCCDPoint(1),pointC(1)],'--rs');hold off;
figure;imshow(imrotate(reg, rad2deg(-phi)));
%% Get rid of sign ambiguity
end

function [ccdVector, maxCCDPoint,pointC] = calcCCD(reg)
b = bwboundaries(reg, 'noholes');
boundaryPoints = b{1};
l = regionprops(reg,'Centroid');
pointC = l.Centroid;
boundaryPointsNorm = [boundaryPoints(:,1) - pointC(:,1),boundaryPoints(:,2) - pointC(:,2)];
ccdVector = (boundaryPointsNorm(:,1).^2 + boundaryPointsNorm(:,2).^2).^0.5;
[~, idx] = max(ccdVector);
maxCCDPoint = boundaryPoints(idx,:);
end


function [phi] = calcLineAngle (points1, points2)
if (points1==points2)
    phi=0;
else
    phi = atan((points1(2) - points2(2)) / (points1(1) - points2(1)));
end
end

function [] = dispPoints (points)
points = int32(points);
xMax = max(points(:,1));
yMax = max(points(:,2));
reg = false(xMax,yMax);
reg(sub2ind(size(reg),points(:,1),points(:,2))) = true;
figure;imshow(reg);
end