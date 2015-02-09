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
Paths.textToImagePath.dir  = 'd:/gimages/images/';
Paths.libsvmPath        = [Paths.basePath 'libsvm-3.20/matlab/'];
Paths.netPath           = 'imagenet-vgg-f.mat';
Paths.classBasePath = 'd:/gimages/images/';
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