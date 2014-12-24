clear; close all; clc;
% %% Configuration
% % See also %%Path
% Net.layer = 19;
% Categorizer.className = {};
% %Categorizer.className{numel(Categorizer.className)} = 'bridge';
% %% Path
% Paths.basePath = '../';
% Paths.rijk = 'vgg-f19_rijks.mat';
% Paths.matconvnetPath    = [Paths.basePath 'matconvnet-1.0-beta7/matlab/vl_setupnn.m'];
% Paths.textToImagePath.bin   = './TextToImage/TextToImage.exe';
% Paths.textToImagePath.dir  = 'd:/gimages/images/';
% Paths.libsvmPath        = [Paths.basePath 'libsvm-3.20/matlab/'];
% Paths.netPath           = 'imagenet-vgg-f.mat';
% %% Load
% run(Paths.matconvnetPath);
% addpath(Paths.libsvmPath);
% Net.net = load('imagenet-vgg-f.mat') ;
% %% Download
% Categorizer = downloadSamples(Paths.textToImagePath, Categorizer);
% %% Extract
% [Net, Categorizer]=cnnFeatureExtract(Net,Categorizer);
% %% Train SVM
% for i=1:numel(unique(Categorizer.classIndex))
%     svm.minX = min(Net.x(:));
%     svm.maxX = max(Net.x(:));
%     svm.X = double((Net.x-svm.minX) / (svm.maxX-svm.minX));
%     svm.y = double(Categorizer.classIndex==i);
%     svm.model = svmtrain(svm.y, svm.X);
%     Net.svm(i) = svm;
% end
save sofar
%% Test SVM
load sofar
rijk = load('vgg-f19_rijks.mat');
i = 1;
svm = Net.svm(i);
Net.minX = min(min(rijk.r()));
Net.maxX = max(max(rijk.r()));
rijk.r = double((rijk.r-svm.minX) / (svm.maxX-svm.minX));
rijk.y = ones(size(rijk.r,1),1);
[label, accuracy, decvalues] = svmpredict(y,rijk.r,svm.model);