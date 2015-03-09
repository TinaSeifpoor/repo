function [ featureVector ] = getFeatureVector( reg, im )
%GETFEATUREVECTOR Summary of this function goes here
%   Detailed explanation goes here
rect2 = smallestRectangle2(reg);
rect = numel(find(reg==1)) / (rect2(3)*rect2(4));
ar = rect2(3)/rect2(4);
mh = meanHue(im, reg);
l = regionprops(reg, 'Eccentricity');
ec = l.Eccentricity;
l = regionprops(reg, 'ConvexArea','Area');
cv = l.Area/l.ConvexArea;
featureVector = [rect,ar,mh,ec,cv];
end