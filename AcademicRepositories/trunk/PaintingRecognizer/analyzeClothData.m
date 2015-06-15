function [imOut,eras] = analyzeClothData(db)
%ANALYZECLOTHDATA Summary of this function goes here
%   Detailed explanation goes here
c = cat(4,db.imCloth);
d = reshape(c,[size(c,1)*size(c,2),size(c,3),size(c,4)]);
f = {db.era};
[eras,~,idxEra]=unique(f);
imOut=[];
for i=1:numel(eras)
    ia = idxEra==i;
    da = d(:,:,ia);
    centerIm = findDominantColor(da);
    imOut = cat(2,imOut,centerIm);
end
end


function centerIm = findDominantColor(im)
imP = permute(im,[1,3,2]);
imP2 = reshape(imP,size(imP,1)*size(imP,2),size(imP,3));
[~,centers,~] = kmeans(double(imP2),5);
centerIm = reshape(uint8(kron(centers,ones([20,1]))),[100,1,3]);
% [~,imax]= min(c3);
% center = centers(imax,:);
end
