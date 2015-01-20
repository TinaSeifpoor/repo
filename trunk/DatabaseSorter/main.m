clear; close all; clc;
%% Configuration
% See also %%Path
Net.layer = 19;
Categorizer.className = {};
% Categorizer.className{numel(Categorizer.className)+1} = 'portrait';
% Categorizer.className{numel(Categorizer.className)+1} = 'painting';
% Categorizer.className{numel(Categorizer.className)+1} = 'stuff';
% Categorizer.className{numel(Categorizer.className)+1} = 'cup';
% Categorizer.className{numel(Categorizer.className)+1} = 'plate';
%% Path
Paths.basePath = '../';
Paths.rijk = 'vgg-f19_rijks.mat';
Paths.matconvnetPath    = [Paths.basePath 'matconvnet-1.0-beta7/matlab/vl_setupnn.m'];
Paths.textToImagePath.bin   = './TextToImage/TextToImage.exe';
Paths.textToImagePath.dir  = 'd:/gimages/images/';
Paths.libsvmPath        = [Paths.basePath 'libsvm-3.20/matlab/'];
Paths.netPath           = 'imagenet-vgg-f.mat';
%% Load
run(Paths.matconvnetPath);
Net.net = load('imagenet-vgg-f.mat') ;
%% Download
Categorizer = downloadSamples(Paths.textToImagePath, Categorizer);
%% Extract
[Net, Categorizer]=cnnFeatureExtract(Net,Categorizer);
%% Train SVM
for i=1:numel(unique(Categorizer.classIndex))
    Net.svm(i) = svmtrain(Net.x, Categorizer.classIndex==i);
end
save sofar
%% Test SVM
load sofar
rijk = load('vgg-f19_rijks.mat');
[classNames,b,~] = unique(Categorizer.className);
classIndices = Categorizer.classIndex(b);
for i=1:numel(b)
    idxPicked = svmclassify(Net.svm(i),rijk.r)==classIndices(i);
    filesPicked = rijk.files(idxPicked);
    for j=1:min([2,numel(filesPicked)])
        figure; 
        filePicked = filesPicked{j};
        imageFile = [filePicked(1:22) 'jpg2' filePicked(28:end-3) 'jpg'];
        imshow(imread(imageFile));title(classNames{i});
    end
end