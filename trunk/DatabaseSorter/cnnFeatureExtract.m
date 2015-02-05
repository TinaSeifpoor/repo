function Class=cnnFeatureExtract(Net,imageFiles, className)
%CNNFEATUREEXTRACT Summary of this function goes here
%   Detailed explanation goes here
nFiles = numel(imageFiles);
successVector=ones(1,nFiles);
for i=1:nFiles
    try
        tic
        filePath = imageFiles{i};
        % obtain and preprocess an image
        im = imread(filePath) ;
        %im_ = single(im) ; % note: 255 range
        im_ = imresize(im, Net.net.normalization.imageSize(1:2)) ;
        im_ = single(im_ - uint8(Net.net.normalization.averageImage));
        
        % run the CNN
        res = vl_simplenn(Net.net, im_);
        Class.X(i,:) = res(Net.layer).x;
        fprintf('%d/%d done in %f...\n', i, nFiles, toc);
    catch
        % on to next one..
        successVector(i)=0;
        Class.X(i,:) = zeros(1,4096);
    end
end
failIndices = successVector==0;
Class.imageFileAll = imageFiles;
Class.imageFile = imageFiles;
Class.className = className;
% Class.className = Categorizer.className;
Class.imageFile(failIndices) = [];
Class.X(failIndices,:) = [];
Class.classNames = repmat(className,[1,numel(Class.imageFile)]);
end

