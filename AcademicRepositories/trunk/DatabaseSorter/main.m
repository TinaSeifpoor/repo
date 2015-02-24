clear; close all; clc;
%% Configuration
% See also %%Path
Net.layer = 19;
Downloader.className = {};
% Downloader.className{numel(Downloader.className)+1} = 'hammer';
% Downloader.className{numel(Downloader.className)+1} = 'tool';
% Downloader.className{numel(Downloader.className)+1} = 'book';
% Downloader.className{numel(Downloader.className)+1} = 'train';
% Downloader.className{numel(Downloader.className)+1} = 'garden';
% Downloader.className{numel(Downloader.className)+1} = 'wardrobe';
% Downloader.className{numel(Downloader.className)+1} = 'sketch';
% Downloader.className{numel(Downloader.className)+1} = 'newspaper';
% Downloader.className{numel(Downloader.className)+1} = 'meditation';
% Downloader.className{numel(Downloader.className)+1} = 'selfie';
% Downloader.className{numel(Downloader.className)+1} = 'bridge';
%% Path
Paths.basePath = '../';
Paths.rijkBase = 'd:/downloads/rijksjpg/jpg2.mat';
Paths.rijkBaseDir = 'd:/downloads/rijksjpg/';
Paths.matconvnetPath    = [Paths.basePath 'matconvnet-1.0-beta7/matlab/vl_setupnn.m'];
Paths.textToImagePath.bin   = './TextToImage/TextToImage.exe';
Paths.textToImagePath.dir  = 'd:/gimages/dbsorter/';
Paths.libsvmPath        = [Paths.basePath 'libsvm-3.20/matlab/'];
Paths.netPath           = 'imagenet-vgg-f.mat';
Paths.classBasePath = 'd:/gimages/dbsorter/';
%% Load
run(Paths.matconvnetPath);
Net.net = load('imagenet-vgg-f.mat') ;
addpath(Paths.libsvmPath);
%% Download
downloadSamples(Paths.textToImagePath, Downloader.className);
%% Discover
[Downloader.imageFile, Downloader.className, ~] = getimagefiles(Paths.textToImagePath.dir);
[uniqueClassNames,~,Downloader.classIndex] = unique(Downloader.className);
for i=1:numel(uniqueClassNames)
    className = uniqueClassNames(i);
    classIndices = strcmp(Downloader.className, className);
    classFile = strcat(Paths.classBasePath,className,'.mat');
    if (exist(classFile{:},'file'))
        currentClass=load(classFile{:});
        currentClass=currentClass.currentClass;
    else
        currentClass=cnnFeatureExtract(Net,Downloader.imageFile(classIndices), className, Paths.textToImagePath.dir);
        save(classFile{:},'currentClass');
    end
    currentClass.classFile = classFile;
    Class(i) = currentClass; %#ok<SAGROW>
end
%% Train SVM
for i=1:numel(Class)
    X = {Class(:).X};
    X(i)=[];
    XNegative = cell2mat(X');
    yNegative = -ones(size(XNegative,1),1);
    XPositive = Class(i).X;
    yPositive = ones(size(XPositive,1),1);
    SVM(i).model = libsvmtrain([XNegative;XPositive], [yNegative;yPositive]);
end
%% Test SVM
currentClass = load(Paths.rijkBase);
rijk = currentClass.currentClass;
classNames = {Class(:).className};
for i=1:numel(classNames)
    className = classNames{i};
    className = className{:};
    [idxPicked, prob] = libsvmpredict(SVM(i).model,rijk.X, 9);
    filesPicked = rijk.imageFile(idxPicked);
    for j=1:numel(filesPicked)
        filePicked = [Paths.rijkBaseDir,filesPicked{j}];
        outputfilename = [className,'/',className,num2str(j),'.jpg'];
        if(~exist(className,'dir'))
            mkdir(className);
        end
        copyfile(filePicked, outputfilename);
    end
end