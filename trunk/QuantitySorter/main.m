clear; close all; clc;
%% Configuration
% See also %%Path
Net.layer = 19;
Downloader.adjectiveName = {};
Downloader.objectName = {};
% Downloader.adjectiveName{numel(Downloader.adjectiveName)+1} = 'a few';
% Downloader.adjectiveName{numel(Downloader.adjectiveName)+1} = 'several';
% Downloader.adjectiveName{numel(Downloader.adjectiveName)+1} = 'lots of';
% Downloader.adjectiveName{numel(Downloader.adjectiveName)+1} = 'dozen';
% Downloader.objectName{numel(Downloader.objectName)+1} = 'cars';
% Downloader.objectName{numel(Downloader.objectName)+1} = 'flowers';
% Downloader.objectName{numel(Downloader.objectName)+1} = 'buildings';
% Downloader.objectName{numel(Downloader.objectName)+1} = 'children';
% Downloader.objectName{numel(Downloader.objectName)+1} = 'books';
% Downloader.objectName{numel(Downloader.objectName)+1} = 'phones';
% Downloader.objectName{numel(Downloader.objectName)+1} = 'planes';
% Downloader.objectName{numel(Downloader.objectName)+1} = 'monitors';
% Downloader.objectName{numel(Downloader.objectName)+1} = 'laptops';
% Downloader.objectName{numel(Downloader.objectName)+1} = 'mouse';
%% Path
Paths.basePath = '../';
Paths.rijk = 'vgg-f19_rijks.mat';
Paths.matconvnetPath    = [Paths.basePath 'matconvnet-1.0-beta7/matlab/vl_setupnn.m'];
Paths.textToImagePath.bin   = './TextToImage/TextToImage.exe';
Paths.textToImagePath.dir  = 'd:/gimages/qasorter/';
Paths.libsvmPath        = [Paths.basePath 'libsvm-3.20/matlab/'];
Paths.netPath           = 'imagenet-vgg-f.mat';
Paths.classBasePath = 'd:/gimages/qasorter/';
%% Load
run(Paths.matconvnetPath);
Net.net = load('imagenet-vgg-f.mat') ;
addpath(Paths.libsvmPath);
%% Download
downloadQuantitySamples(Paths.textToImagePath, Downloader.adjectiveName, Downloader.objectName);
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
    %     X = [XNegative;XPositive];
    %     y = [yNegative;yPositive];
    %     save('svm_sample.mat','X','y');
end
%% Test SVM
load('db.mat');
classNames = {Class(:).className};
for i=1:numel(classNames)
    [idxPicked, prob] = libsvmpredict(SVM(i).model,DB.Net.X, 5);
    filesPicked = DB.Categorizer.imageFile(idxPicked);
    for j=1:numel(filesPicked)
        filePicked = filesPicked{j};
        imcur = imread(filePicked);
        %         figure;imshow(imcur);title(classNames{i});
        outputfilename = strcat(classNames{i},num2str(j),'.jpg');
        imwrite(imcur,outputfilename{:});
    end
end