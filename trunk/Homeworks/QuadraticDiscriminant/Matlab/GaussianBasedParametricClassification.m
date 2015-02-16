function [confusionMatrix, performance] = GaussianBasedParametricClassification( means, covars, priors, dataSet )
%GAUSSIANBASEDPARAMETERCLASSIFICATION Calculates Quadratic Discriminant
nClasses = size(dataSet,1);
performance = cell(nClasses,2);
confusionMatrix = zeros(nClasses,nClasses,'uint8');
for k=1:nClasses
    performance{k,1} = dataSet{k,1};
    nClassInstances = size(dataSet{k,2},1);
    resultList = zeros(nClassInstances,1,'uint8');
    classFeatureList = dataSet{k,2};
    for x=1:nClassInstances
        instanceFeatureVector = classFeatureList(x,:);
        probVector = zeros(nClasses,1);
        for i=1:nClasses
            classMean = means(i,:);
            classCovar = covars{i};
            classPrior = priors(i,:);
            probVector(i)= -0.5 * log(det(classCovar))-0.5*(instanceFeatureVector-classMean)*inv(classCovar)*(instanceFeatureVector-classMean)'+log(classPrior);
        end
        classifiedClass = (find(probVector==max(probVector)));
        resultList(x) = (classifiedClass==k);
        confusionMatrix(k,classifiedClass)=confusionMatrix(k,classifiedClass)+1;
    end
    performance{k,2} = mean(resultList);
end

end

