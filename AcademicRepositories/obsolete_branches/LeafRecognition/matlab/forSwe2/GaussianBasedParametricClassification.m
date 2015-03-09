function prediction = GaussianBasedParametricClassification( means, covars, priors, measurements )
%GAUSSIANBASEDPARAMETERCLASSIFICATION Calculates Quadratic Discriminant
nClasses = size(means,1);
prediction = zeros(size(measurements,1),1);
for x=1:numel(prediction)
    instanceFeatureVector = measurements(x,:);
    probVector = zeros(nClasses,1);
    for i=1:nClasses
        classMean = means(i,:);
        classCovar = covars{i};
        classPrior = priors(i,:);
        probVector(i)= -0.5 * log(det(classCovar))-0.5*(instanceFeatureVector-classMean)/classCovar*(instanceFeatureVector-classMean)'+log(classPrior);
    end
    prediction(x) = (find(probVector==max(probVector)));
end

end

