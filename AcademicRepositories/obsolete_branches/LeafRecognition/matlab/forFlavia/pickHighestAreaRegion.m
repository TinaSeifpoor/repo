function [ regLeaf ] = pickHighestAreaRegion( reg )
%PICKHIGHESTAREAREGION Summary of this function goes here
%   Detailed explanation goes here
try
propertiesReg = regionprops(reg,'Area');
labelTh = bwlabel(reg);
areaList = [propertiesReg.Area];
[~, idxLeaf] = max(areaList);
regLeaf = (labelTh==idxLeaf);
regLeaf = imfill(regLeaf,'holes');
catch a
    b=5;
end

