clear;clc;close all;
%% Read data
fid = fopen('dataset.txt', 'rt');
dataset = textscan(fid,'%s','Delimiter',',','CollectOutput',1);
fclose(fid);
dataset = char(regexprep(dataset{:},'[\s'']',''));
datasetCopy = double(dataset);
datasetLabels = unique(dataset);
nLabels = numel(datasetLabels);
nObserv = size(dataset,1);
for idxLabel = 1:nLabels
    datasetCopy(dataset==datasetLabels(idxLabel)) = idxLabel;
end
dataset = datasetCopy;
clear datasetCopy fid idxLabel ans;
%% Constants
trainSet = dataset(1:300,:);
validSet = dataset(301:500,:);
maxIters=500;
%% Initialization
NList=[2,3,5];
logProbTrain = zeros(size(trainSet,1),numel(NList));
logProbValid = zeros(size(validSet,1),numel(NList));
for idxN= 1:numel(NList)
    N = NList(idxN);
    transInitial = rowStochastic(rand(N));
    emisInitial = rowStochastic(rand(N,nLabels));
    initProbInitial = rowStochastic(zeros(1,N)+1/N);
%     [transEst, emisEst, initProbEst, logProbTrain(:,idxN)] = HMMtrain(trainSet, transInitial, emisInitial, initProbInitial, maxIters);
    [transEst, emisEst] = hmmtrain(trainSet, transInitial, emisInitial, 'tolerance', '1.4e-3');
    for i = 1:size(trainSet,1)
        [~, logProbTrain(i, idxN)]=hmmdecode(trainSet(i,:), transEst, emisEst);
    end
    for i = 1:size(validSet,1)
        [~, logProbValid(i, idxN)]=hmmdecode(validSet(i,:), transEst, emisEst);
    end
%     [~, ~, ~, logProbValid(:,idxN)] = HMMtrain(validSet, transEst, emisEst, initProbEst, 1);
    SLabels = strcat('S',num2str((1:N)'));
    TLabels = {'A','B'};
    labels.X = SLabels; labels.Y = SLabels;
    reportMatrix(transInitial, labels,...
      ['transInitial_' num2str(N) '.eps']);
    labels.X = SLabels; labels.Y = SLabels;
    reportMatrix(transEst, labels,...
      ['transEst_' num2str(N) '.eps']);
    labels.X = TLabels; labels.Y = SLabels;
    reportMatrix(emisInitial, labels,...
      ['emitInitial_' num2str(N) '.eps']);
    labels.X = TLabels; labels.Y = SLabels;
    reportMatrix(emisEst, labels,...
      ['emitEst_' num2str(N) '.eps']);
    labels.X = 1; labels.Y = SLabels;
    reportMatrix(initProbInitial, labels,...
      ['initProbInitial_' num2str(N) '.eps']);
%     labels.X = SLabels; labels.Y = 1;
%     reportMatrix(initProbEst, labels,...
%       ['initProbEst_' num2str(N) '.eps']);
end
%% Report results
reportLogprob(reshape(logProbTrain,50,18),'trainLogprob.eps');
reportLogprob(reshape(logProbValid,50,12),'validLogprob.eps');
