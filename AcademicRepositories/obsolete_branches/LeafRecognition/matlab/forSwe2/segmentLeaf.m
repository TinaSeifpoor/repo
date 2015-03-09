function [ regLeaf ] = segmentLeaf( imRGB )
%SEGMENTIMAGE Summary of this function goes here
%   Detailed explanation goes here

imHSV = rgb2hsv(imRGB);
imSat = imHSV(:,:,2);
im1 = imRGB(:,:,3);
im2 = 1 - imSat;
imLeaf = im1*.5 + uint8(im2*128);
regTh = imLeaf<210;
regLeaf = pickHighestAreaRegion(regTh);
end