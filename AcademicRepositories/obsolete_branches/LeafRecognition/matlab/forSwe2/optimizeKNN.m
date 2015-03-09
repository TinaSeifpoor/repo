function perfK = optimizeKNN(speciesTrain, featListTrain, kList)
%OPTIMIZEKNN Summary of this function goes here
%   Detailed explanation goes here

nSpecies = numel(unique(speciesTrain));
idxListXVal = crossvalind('kfold', speciesTrain);
perfK = zeros(nSpecies,5,numel(kList));
for idxK = 1:numel(kList)
    k = kList(idxK);
    perfXVal = zeros(nSpecies,5);
    for idxXVal = 1:5
        idxListXValTrain = idxListXVal ~= idxXVal;
        idxListXValValid = idxListXVal == idxXVal;
        speciesTrainT = speciesTrain(idxListXValTrain);
        speciesTrainV = speciesTrain(idxListXValValid);
        featListTrainT = featListTrain(:,idxListXValTrain);
        featListTrainV = featListTrain(:,idxListXValValid);
        speciesTrainVPre=knnclassify(featListTrainV', featListTrainT', speciesTrainT, k);
        [~, perfXVal(:,idxXVal)] = genConfusionMatrix(speciesTrainV, speciesTrainVPre);
    end
    perfK(:,:,idxK) = perfXVal(:,:);
end
end

