function [ ncch ] = calcNCCH( reg )
%CALCNCCH Summary of this function goes here
%   Detailed explanation goes here
boundaryPoints = bwboundaries(reg);
boundaryPoints = boundaryPoints{1};

chainCode = zeros(size(boundaryPoints,1),1);
diffCoordList = boundaryPoints(1:size(boundaryPoints,1)-1,:) - boundaryPoints(2:size(boundaryPoints,1),:);
cchDir{1}=[1,0];
cchDir{2}=[1,-1];
cchDir{3}=[0,-1];
cchDir{4}=[-1,-1];
cchDir{5}=[-1,0];
cchDir{6}=[-1,1];
cchDir{7}=[0,1];
cchDir{8}=[1,1];
% cchMag(1:2:7) = 1;
% cchMag(2:2:8) = 2^0.5;
cchMag = zeros(1,numel(cchDir));
for idx=1:numel(cchDir)
    cchDirSelected = cchDir{idx};
    idxDir = diffCoordList(:, 1) == cchDirSelected(:,1) & diffCoordList(:, 2) == cchDirSelected(:,2);
    cchMag(idx) = sum(cchDir{idx}.^2).^0.5;
    chainCode(idxDir) = idx;
end
cch = hist(chainCode, 1:numel(cchDir));
%%
ncch = cch .* cchMag;
ncch = ncch/sum(ncch);

end

