clear;clc;close all;
load('leaf-all');
load('idxTest');
%% Determine nHarmonics
nHarmonics = 20:20:400;
%nHarmonics = 150:5:250;
[fftXMListTrain, ~, ~, ~]...
    = SplitDataset(idxTest, species, fftXMList');
[fftYMListTrain, speciesTrain, ~, ~]...
    = SplitDataset(idxTest, species, fftYMList');
fftXMListTrain = log(fftXMListTrain); fftYMListTrain=log(fftYMListTrain);
maxVal = max(max([fftXMListTrain,fftYMListTrain]));minVal = min(min([fftXMListTrain,fftYMListTrain]));

fftXMListTrain = ((fftXMListTrain - minVal) / (maxVal-minVal));
fftYMListTrain = ((fftYMListTrain - minVal) / (maxVal-minVal));

perfHarmonic = optimizeFD(speciesTrain, fftXMListTrain, fftYMListTrain, nHarmonics,[32,0.574349177498517]);
perfXVal = squeeze(mean(mean(perfHarmonic,2)));
plot(nHarmonics,1-perfXVal);
% xlabel('Karma\c{s}{\i}kl{\i}k (harmonik say{\i}s{\i})','Interpreter','latex');ylabel('\c{C}apraz Do\u{g}rulama Hatas{\i}','Interpreter','latex');
xlabel('Complexity (nHarmonics)');ylabel('Cross validation error');
xlim([min(nHarmonics) max(nHarmonics)]);
% %% Determine weights
% nHarmonics = 180;
% [fftXMListTrain, ~, ~, ~]...
%     = SplitDataset(idxTest, species, fftXMList');
% [fftYMListTrain, speciesTrain, ~, ~]...
%     = SplitDataset(idxTest, species, fftYMList');
% 
% fdNormalizer(1) = max(max(log([fftXMListTrain,fftYMListTrain])));
% fdNormalizer(2) = min(min(log([fftXMListTrain,fftYMListTrain])));
% 
% fftXMListTrain = ((log(fftXMListTrain) - fdNormalizer(2)) / (fdNormalizer(1)-fdNormalizer(2)));
% fftYMListTrain = ((log(fftYMListTrain) - fdNormalizer(2)) / (fdNormalizer(1)-fdNormalizer(2)));
% featListTrain = [fftXMListTrain(1:nHarmonics,:); fftYMListTrain(1:nHarmonics,:)];
% 
% % [perfXVal, svmParams] = optimizeSVM(speciesTrain, featListTrain');
% svmParams = [32,0.574349177498517];
% perfHarmonic = optimizeFD(speciesTrain, fftXMListTrain, fftYMListTrain, nHarmonics, svmParams);
% fdWeights = squeeze(mean(perfHarmonic,2));
% plot(fdWeights,'--rs');
% xlabel('Species');ylabel('Weights (5-fold crossvalidation performance)')
% xlim([1 32]);
% save('leaf-fdForCascade', 'species', 'idxTest', 'fftXMList', 'fftYMList', 'fdWeights', 'nHarmonics', 'fdNormalizer', 'svmParams');