function [Net, Categorizer]=cnnFeatureExtract(Net,Categorizer)
%CNNFEATUREEXTRACT Summary of this function goes here
%   Detailed explanation goes here
nFiles = numel(Categorizer.imageFile);
successVector=ones(1,nFiles);
for i=1:nFiles
    try
        tic
        filePath = Categorizer.imageFile{i};
        % obtain and preprocess an image
        im = imread(filePath) ;
        %im_ = single(im) ; % note: 255 range
        im_ = imresize(im, Net.net.normalization.imageSize(1:2)) ;
        im_ = single(im_ - uint8(Net.net.normalization.averageImage));
        
        % run the CNN
        res = vl_simplenn(Net.net, im_);
        Net.x(i,:) = res(Net.layer).x;
        fprintf('%d/%d done in %f...\n', i, nFiles, toc);
    catch
        % on to next one..
        successVector(i)=0;
    end
end
failIndices = successVector==0;
Categorizer.imageFile(failIndices)=[];
Categorizer.className(failIndices)=[];
Categorizer.classIndex(failIndices)=[];
Net.x(failIndices,:)=[];
end

