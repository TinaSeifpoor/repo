clear;clc;close all;
%% Read data
fid = fopen('featurevectors.csv', 'rt');
dataset = textscan(fid,'%f %f %f %f %s','Delimiter',',','CollectOutput',1);
fclose(fid);
%% Sort dataset
[trainSet, testSet] = SortDataset(dataset{2}, dataset{1}, 0.6);
%% Case 1 - Quadratic Discriminant
[means1, covariances1, priors1] = CalculateParameters(trainSet,1);
[confusionMatrixTraining1, performanceTraining1] =GaussianBasedParametricClassification(means1, covariances1, priors1, trainSet);
[confusionMatrixTesting1, performanceTesting1] =GaussianBasedParametricClassification(means1, covariances1, priors1, testSet);
%% Case 2 - Linear Discriminant
[means2, covariances2, priors2] = CalculateParameters(trainSet,2);
[confusionMatrixTraining2, performanceTraining2] =GaussianBasedParametricClassification(means2, covariances2, priors2, trainSet);
[confusionMatrixTesting2, performanceTesting2] =GaussianBasedParametricClassification(means2, covariances2, priors2, testSet);
%% Case 3 - Naive Bayes' Classifier
[means3, covariances3, priors3] = CalculateParameters(trainSet,3);
[confusionMatrixTraining3, performanceTraining3] =GaussianBasedParametricClassification(means3, covariances3, priors3, trainSet);
[confusionMatrixTesting3, performanceTesting3] =GaussianBasedParametricClassification(means3, covariances3, priors3, testSet);
%% Case 4 - Euclidean Distance
[means4, covariances4, priors4] = CalculateParameters(trainSet,4);
[confusionMatrixTraining4, performanceTraining4] =GaussianBasedParametricClassification(means4, covariances4, priors4, trainSet);
[confusionMatrixTesting4, performanceTesting4] =GaussianBasedParametricClassification(means4, covariances4, priors4, testSet);
%% Bonus
bonusDataset = dataset;
%% Reshape dataset into two features
featureList = bonusDataset{1,1};
featureList(:,1:2) = [];
bonusDataset{1,1} = featureList;
%% Sort dataset
[bonusTrainSet, bonusTestSet] = SortDataset(bonusDataset{2}, bonusDataset{1}, 0.6);
%% Case 1 - Quadratic Discriminant
[bonusMeans1, bonusCovariances1, bonusPriors1] = CalculateParameters(bonusTrainSet,1);
[bonusConfusionMatrixTraining1, bonusPerformanceTraining1] =GaussianBasedParametricClassification(bonusMeans1, bonusCovariances1, bonusPriors1, bonusTrainSet);
[bonusConfusionMatrixTesting1, bonusPerformanceTesting1] =GaussianBasedParametricClassification(bonusMeans1, bonusCovariances1, bonusPriors1, bonusTestSet);
%% Display Case 1
PlotResults(bonusMeans1, bonusCovariances1);
%% Case 2 - Linear Discriminant
[bonusMeans2, bonusCovariances2, bonusPriors2] = CalculateParameters(bonusTrainSet,2);
[bonusConfusionMatrixTraining2, bonusPerformanceTraining2] =GaussianBasedParametricClassification(bonusMeans2, bonusCovariances2, bonusPriors2, bonusTrainSet);
[bonusConfusionMatrixTesting2, bonusPerformanceTesting2] =GaussianBasedParametricClassification(bonusMeans2, bonusCovariances2, bonusPriors2, bonusTestSet);
%% Display Case 2
PlotResults(bonusMeans2, bonusCovariances2);
%% Case 3 - Naive Bayes' Classifier
[bonusMeans3, bonusCovariances3, bonusPriors3] = CalculateParameters(bonusTrainSet,3);
[bonusConfusionMatrixTraining3, bonusPerformanceTraining3] =GaussianBasedParametricClassification(bonusMeans3, bonusCovariances3, bonusPriors3, bonusTrainSet);
[bonusConfusionMatrixTesting3, bonusPerformanceTesting3] =GaussianBasedParametricClassification(bonusMeans3, bonusCovariances3, bonusPriors3, bonusTestSet);
%% Display Case 3
PlotResults(bonusMeans3, bonusCovariances3);
%% Case 4 - Euclidean Distance
[bonusMeans4, bonusCovariances4, bonusPriors4] = CalculateParameters(bonusTrainSet,4);
[bonusConfusionMatrixTraining4, bonusPerformanceTraining4] =GaussianBasedParametricClassification(bonusMeans4, bonusCovariances4, bonusPriors4, bonusTrainSet);
[bonusConfusionMatrixTesting4, bonusPerformanceTesting4] =GaussianBasedParametricClassification(bonusMeans4, bonusCovariances4, bonusPriors4, bonusTestSet);
%% Display Case 4
PlotResults(bonusMeans4, bonusCovariances4);