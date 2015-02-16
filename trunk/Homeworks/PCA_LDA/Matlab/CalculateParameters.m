function [means, covariances, prior] = CalculateParameters(features, ...
    classes, caseIdx)
%CALCULATEPARAMETERS Calculates means, covariances and priors
nClasses = numel(unique(classes));
nFeatures = size(features,2);
means=zeros(nClasses,nFeatures);
prior = zeros(nClasses,1);
nInstances = 0;
for i=1:nClasses
    means(i,:)= mean(features(classes==i,:));
    prior(i) = length(features(classes==i,:));
    nInstances = nInstances + prior(i);
end
prior = prior./nInstances;
switch (caseIdx)
    case 1
        covariances=cell(nClasses,1);
        for i=1:nClasses
            covariances{i} = cov(features(classes==i,:));
        end
    case 2
        covariance = zeros(nFeatures,nFeatures);
        for i=1:nClasses
            covariance = covariance + cov(features(classes==i,:))*prior(i);
        end
        covariances = cell(nClasses,1);
        for i=1:nClasses
            covariances{i} = covariance;
        end
    case 3
        variance = zeros(nFeatures,nFeatures);
        for i=1:nClasses
            variance = variance + diag(var(features(classes==i,:))*prior(i));
        end
        covariances = cell(nClasses,1);
        for i=1:nClasses
            covariances{i} = variance;
        end
    case 4
        covariances = cell(nFeatures,1);
        identity = eye(nFeatures);
        for i=1:nClasses
            covariances{i} = identity;
        end
end
end

