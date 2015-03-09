function perfXVal = optimizeGlobal(speciesTrain, featListTrain)
%OPTIMIZEGLOBAL Summary of this function goes here
%   Detailed explanation goes here

nSpecies = numel(unique(speciesTrain));
idxListXVal = crossvalind('kfold', speciesTrain);
perfXVal = zeros(nSpecies,5);
for idxXVal = 1:5
    idxListXValTrain = idxListXVal ~= idxXVal;
    idxListXValValid = idxListXVal == idxXVal;
    speciesTrainT = speciesTrain(idxListXValTrain);
    speciesTrainV = speciesTrain(idxListXValValid);
    featListTrainT = featListTrain(:,idxListXValTrain);
    featListTrainV = featListTrain(:,idxListXValValid);
    [means, covariances, priors] = CalculateParameters(featListTrainT',speciesTrainT,1);
    speciesTrainVPre =...
        GaussianBasedParametricClassification(means, covariances, priors, featListTrainV');
    [~, perfXVal(:,idxXVal)] = genConfusionMatrix(speciesTrainV, speciesTrainVPre);
end
end

