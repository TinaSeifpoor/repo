clear; close all; clc;
%% Configuration
% See also %%Path
Net.layer = 19;
Downloader.className = {};
% Downloader.className{numel(Downloader.className)+1} = 'portrait';
% Downloader.className{numel(Downloader.className)+1} = 'painting';
% Downloader.className{numel(Downloader.className)+1} = 'stuff';
% Downloader.className{numel(Downloader.className)+1} = 'cup';
% Downloader.className{numel(Downloader.className)+1} = 'plate';
%% Path
Paths.basePath = '../';
Paths.rijk = 'vgg-f19_rijks.mat';
Paths.matconvnetPath    = [Paths.basePath 'matconvnet-1.0-beta7/matlab/vl_setupnn.m'];
Paths.textToImagePath.bin   = './TextToImage/TextToImage.exe';
Paths.textToImagePath.dir  = 'e:/gimages/images/';
Paths.libsvmPath        = [Paths.basePath 'libsvm-3.20/matlab/'];
Paths.netPath           = 'imagenet-vgg-f.mat';
Paths.classBasePath = 'e:/gimages/images/';
%% Load
run(Paths.matconvnetPath);
Net.net = load('imagenet-vgg-f.mat') ;
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
        currentClass=cnnFeatureExtract(Net,Downloader.imageFile(classIndices), className);
        save(classFile{:},'currentClass');
    end
    currentClass.classFile = classFile;
    Class(i) = currentClass; %#ok<SAGROW>
end
%% Train SVM
for i=1:numel(Class)
    if (exist('Class(i).svm.model','var'))
        currentClass=load(classFile{:});
        currentClass=currentClass.currentClass;
        Class(i) = currentClass;
    else
        X = {Class(:).X};
        X(i)=[];
        XNegative = cell2mat(X');
        yNegative = -ones(size(XNegative,1),1);
        XPositive = Class(i).X;
        yPositive = ones(size(XPositive,1),1);
        Class(i).svm.model = svmtrain([XNegative;XPositive], [yNegative;yPositive]);
        currentClass = Class(i);
        save(Class(i).classFile{:},'currentClass');
    end
end
%% Test SVM
load('db.mat');
classNames = {Class(:).className};
for i=1:numel(classNames)
    idxPicked = svmclassify(Class(i).svm.model,DB.Net.X)==1;
    filesPicked = DB.Categorizer.imageFile(idxPicked);
    for j=1:min([2,numel(filesPicked)])
        figure;
        filePicked = filesPicked{j};
%         imshow(imread(filePicked));title(classNames{i});
    end
end