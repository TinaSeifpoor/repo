clear;clc;close all;
load('leaf-all');
load('idxTest');
[featListTrain, speciesTrain, ~, ~]...
    = SplitDataset(idxTest, species, meas');
perfXVal = optimizeGlobal(speciesTrain, featListTrain);
globWeights = squeeze(mean(perfXVal,2));
plot(globWeights,'--rs');
xlabel('Species');ylabel('Weights (5-fold crossvalidation performance)')
xlim([1 32]);
save('leaf-globForCascade', 'species', 'idxTest', 'meas', 'globWeights');

