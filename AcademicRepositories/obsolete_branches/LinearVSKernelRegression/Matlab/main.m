clear;clc;close all;
%% Read data
fid = fopen('dataset.csv', 'rt');
dataset = textscan(fid,'%f %f','Delimiter',',','CollectOutput',1);
fclose(fid);
dataset = dataset{:};
%% Constants
hList = (12:-1:.01)*.01;
nH = numel(hList);
nList = 1:18;
nN = numel(nList);
nFolds = 10;
nonParamMaxProximity=0.2;
nonParamStep=0.1;
%% Repeat for 10 times
nRedo = 10;
perfParametric = zeros(nRedo,nN);
perfNonparametric = zeros(nRedo,nH);
for idxRedo=1:nRedo
    %% Generate 10 folds
    indices = mycrossvalind(dataset,nFolds);
    %% Fit polynomials parametric
    errorParametric = zeros(nFolds,nN);
    errorNonparametric = zeros(nFolds,nH);
    for idxFold=1:nFolds
        valDataset = dataset(indices==idxFold,:);
        traDataset = dataset(indices~=idxFold,:);
        %% Parametric
        [~,errorParametric(idxFold,:)] = ...
            CalcValuesPolynomials(traDataset, valDataset, nList);
        %% Non-parametric
        [~,errorNonparametric(idxFold,:)] = ...
            CalcValuesKernel(traDataset,valDataset,hList);
    end
    perfParametric(idxRedo,:) = trimmean(errorParametric,20)';
    perfNonparametric(idxRedo,:) = trimmean(errorNonparametric,20)';
end

DispFits(perfParametric,dataset,nList,'n');
DispFits(perfNonparametric,dataset,hList,'h');