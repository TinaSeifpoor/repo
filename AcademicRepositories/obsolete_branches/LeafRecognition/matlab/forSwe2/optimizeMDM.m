function [] = optimizeMDM(kList, species, idxTest, featBMDMList,...
    featAMDMList, featMMDMList)
%OPTIMIZEMDM Summary of this function goes here
%   Detailed explanation goes here
[featListTrain, speciesTrain, ~, ~]...
    = SplitDataset(idxTest, species, featBMDMList);
%
perfK = optimizeKNN(speciesTrain, featListTrain, kList);
avgPerf = squeeze(mean(mean(perfK,2)));
plot(kList,1-avgPerf,'r');hold on;
%%
[featListTrain, speciesTrain, ~, ~]...
    = SplitDataset(idxTest, species, featAMDMList);
%
perfK = optimizeKNN(speciesTrain, featListTrain, kList);
avgPerf = squeeze(mean(mean(perfK,2)));
plot(kList,1-avgPerf,'b');
%%
[featListTrain, speciesTrain, ~, ~]...
    = SplitDataset(idxTest, species, featMMDMList);
%
perfK = optimizeKNN(speciesTrain, featListTrain, kList);
avgPerf = squeeze(mean(mean(perfK,2)));
plot(kList,1-avgPerf,'g');
legend('Basic MDM', 'Average MDM', 'Maximum MDM');
xlabel('Complexity (k)');ylabel('Error (1 - mean performance)');

end

