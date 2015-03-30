clear; close all; clc;
%% Configuration
% See also %%Path
Net.layer = 19;
%% Path
Paths.basePath = '../';
Paths.rijkBase = 'd:/downloads/rijksjpg/';
Paths.rijk = 'vgg-f19_rijks.mat';
Paths.matconvnetPath    = [Paths.basePath 'matconvnet-1.0-beta7/matlab/vl_setupnn.m'];
Paths.netPath           = 'imagenet-vgg-f.mat';
%% Load
run(Paths.matconvnetPath);
Net.net = load('imagenet-vgg-f.mat') ;
%% Discover
[rijk.imageFile, rijk.className, ~] = getimagefiles(Paths.rijkBase);
[uniqueClassNames,~,rijk.classIndex] = unique(rijk.className);
for i=1:numel(uniqueClassNames)
    className = uniqueClassNames(i);
    classIndices = strcmp(rijk.className, className);
    classFile = strcat(Paths.rijkBase,className,'.mat');
    if (exist(classFile{:},'file'))
        currentClass=load(classFile{:});
        currentClass=currentClass.currentClass;
    else
        currentClass=cnnFeatureExtract(Net,rijk.imageFile(classIndices), className, Paths.rijkBase);
        save(classFile{:},'currentClass');
    end
    currentClass.classFile = classFile;
    Class = currentClass;
end