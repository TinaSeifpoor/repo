function [confusionMatrix] = ...
    GaussianBasedParametricClassification( means, covars, priors, ...
    features, classes )
%GAUSSIANBASEDPARAMETERCLASSIFICATION Calculates Quadratic Discriminant
nClasses = numel(unique(classes));
confusionMatrix = zeros(nClasses,nClasses,'uint8');
for k=1:nClasses
    nClassInstances = size(features(classes==k),1);
    resultList = zeros(nClassInstances,1,'uint8');
    classFeatureList = features(classes==k,:);
    for x=1:nClassInstances
        instanceFeatureVector = classFeatureList(x,:);
        probVector = zeros(nClasses,1);
        for i=1:nClasses
            classMean = means(i,:);
            classCovar = covars{i};
            classPrior = priors(i,:);
            probVector(i)= -0.5 * log(det(classCovar))-0.5*...
                (instanceFeatureVector-classMean)*inv(classCovar)*...
                (instanceFeatureVector-classMean)'+log(classPrior);
        end
        classifiedClass = (find(probVector==max(probVector)));
        resultList(x) = (classifiedClass==k);
        confusionMatrix(k,classifiedClass)=confusionMatrix(k,classifiedClass)+1;
    end
end

end

