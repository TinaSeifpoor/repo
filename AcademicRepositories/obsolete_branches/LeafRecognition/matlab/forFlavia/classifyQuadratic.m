function [ confusionMatrixTesting, confusionMatrixTraining, perfTesting, perfTraining  ] = classifyQuadratic( measTrain, measTest, speciesTrain, speciesTest )
%CLASSIFYQUADRATIC Summary of this function goes here
%   Detailed explanation goes here
[means, covariances, priors] = CalculateParameters(measTrain,speciesTrain,1);
[confusionMatrixTraining] =GaussianBasedParametricClassification(means, covariances, priors, speciesTrain, measTrain);
confusionMatrixTraining = bsxfun(@rdivide,confusionMatrixTraining,sum(confusionMatrixTraining));
confusionMatrixTraining(isnan(confusionMatrixTraining)) = 0;
[confusionMatrixTesting] =GaussianBasedParametricClassification(means, covariances, priors, speciesTest, measTest);
confusionMatrixTesting = bsxfun(@rdivide,confusionMatrixTesting,sum(confusionMatrixTesting));
confusionMatrixTesting(isnan(confusionMatrixTesting)) = 0;
perfTesting = diag(confusionMatrixTesting);perfTraining = diag(confusionMatrixTraining);


end

