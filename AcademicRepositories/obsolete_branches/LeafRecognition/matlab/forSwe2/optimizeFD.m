function perfHarmonic = optimizeFD(speciesTrain, fftXMList, fftYMList, harmonicList, svmParams)
%OPTIMIZEKNN Summary of this function goes here
%   Detailed explanation goes here

nSpecies = numel(unique(speciesTrain));
nFold = 5;
idxListXVal = crossvalind('kfold', speciesTrain, nFold);
perfHarmonic = zeros(nSpecies,nFold,numel(harmonicList));
for idxH = 1:numel(harmonicList)
    h = harmonicList(idxH);
    featListTrain = [fftXMList(1:h,:);fftYMList(1:h,:)];
    perfXVal = zeros(nSpecies,nFold);
    for idxXVal = 1:nFold
        idxListXValTrain = idxListXVal ~= idxXVal;
        idxListXValValid = idxListXVal == idxXVal;
        speciesTrainT = speciesTrain(idxListXValTrain);
        speciesTrainV = speciesTrain(idxListXValValid);
        featListTrainT = featListTrain(:,idxListXValTrain);
        featListTrainV = featListTrain(:,idxListXValValid);
        svmModel = svmtrain(speciesTrainT, featListTrainT',sprintf('-q -c %f -g %f', svmParams(1), svmParams(2)));
        [speciesTrainVPre, ~] = svmpredict(speciesTrainV, ...
        featListTrainV', svmModel, '-q');
%         speciesTrainVPre = multisvm(featListTrainT', speciesTrainT', featListTrainV');
%         [means, covariances, priors] = CalculateParameters(featListTrainT',speciesTrainT,1);
%         speciesTrainVPre =...
%             GaussianBasedParametricClassification(means, covariances, priors, featListTrainV');
        [~, perfXVal(:,idxXVal)] = genConfusionMatrix(speciesTrainV, speciesTrainVPre);
    end
    perfHarmonic(:,:,idxH) = perfXVal(:,:);
end
end

