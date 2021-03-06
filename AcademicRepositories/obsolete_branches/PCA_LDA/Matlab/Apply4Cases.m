function [...
    confusionMatrixTraining1, confusionMatrixTesting1,...
    confusionMatrixTraining2, confusionMatrixTesting2,...
    confusionMatrixTraining3, confusionMatrixTesting3,...
    confusionMatrixTraining4, confusionMatrixTesting4]...
    = Apply4Cases(trainFeatures, trainClasses, ...
    testFeatures, testClasses, isDisp, keyword)
%APPLY4CASES Summary of this function goes here
%   Detailed explanation goes here
%% Case 4 - Euclidean Distance
[means4, covariances4, priors4] = CalculateParameters(trainFeatures,...
    trainClasses ,4);
confusionMatrixTraining4 =...
    GaussianBasedParametricClassification(means4, covariances4, priors4,...
    trainFeatures, trainClasses);
confusionMatrixTesting4 =...
    GaussianBasedParametricClassification(means4, covariances4, priors4,...
    testFeatures, testClasses);
%% Display Case 4
if (isDisp)
    [x1ListOut, x2ListOut] = PlotResults(means4, covariances4, [keyword '4']);
    PlotConfusion(confusionMatrixTraining4, [keyword 'ConfusionMatrixTrain4']);
    PlotConfusion(confusionMatrixTesting4 , [keyword 'ConfusionMatrixTest4']);
end
%% Case 3 - Naive Bayes' Classifier
[means3, covariances3, priors3] = CalculateParameters(trainFeatures,...
    trainClasses, 3);
confusionMatrixTraining3 =...
    GaussianBasedParametricClassification(means3, covariances3, priors3,...
    trainFeatures, trainClasses);
confusionMatrixTesting3 =...
    GaussianBasedParametricClassification(means3, covariances3, priors3,...
    testFeatures, testClasses);
%% Display Case 3
if (isDisp)
    PlotResults(means3, covariances3, [keyword '3'], x1ListOut, x2ListOut);
    PlotConfusion(confusionMatrixTraining3, [keyword 'ConfusionMatrixTrain3']);
    PlotConfusion(confusionMatrixTesting3 , [keyword 'ConfusionMatrixTest3']);
end
%% Case 2 - Linear Discriminant
[means2, covariances2, priors2] = CalculateParameters(trainFeatures,...
    trainClasses, 2);
confusionMatrixTraining2 =...
    GaussianBasedParametricClassification(means2, covariances2, priors2,...
    trainFeatures, trainClasses);
confusionMatrixTesting2 =...
    GaussianBasedParametricClassification(means2, covariances2, priors2,...
    testFeatures, testClasses);
%% Display Case 2
if (isDisp)
    PlotResults(means2, covariances2, [keyword '2'], x1ListOut, x2ListOut);
    PlotConfusion(confusionMatrixTraining2, [keyword 'ConfusionMatrixTrain2']);
    PlotConfusion(confusionMatrixTesting2 , [keyword 'ConfusionMatrixTest2']);
end
%% Case 1 - Quadratic Discriminant
[means1, covariances1, priors1] = CalculateParameters(trainFeatures,...
    trainClasses, 1);
confusionMatrixTraining1 =...
    GaussianBasedParametricClassification(means1, covariances1, priors1,...
    trainFeatures, trainClasses);
confusionMatrixTesting1 =...
    GaussianBasedParametricClassification(means1, covariances1, priors1,...
    testFeatures, testClasses);
%% Display Case 1
if (isDisp)
    PlotResults(means1, covariances1, [keyword '1'], x1ListOut, x2ListOut);
    PlotConfusion(confusionMatrixTraining1, [keyword 'ConfusionMatrixTrain1']);
    PlotConfusion(confusionMatrixTesting1 , [keyword 'ConfusionMatrixTest1']);
end

end
% 
