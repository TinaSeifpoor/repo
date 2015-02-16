function [means, covariances, prior] = CalculateParameters(trainSet, caseIdx)
%CALCULATEPARAMETERS Calculates means, covariances and priors
nClasses = size(trainSet,1);
nFeatures = size(trainSet{1,2},2);
means=zeros(nClasses,nFeatures);
prior = zeros(nClasses,1);
nInstances = 0;
for i=1:nClasses
    means(i,:)= mean(trainSet{i,2});
    prior(i) = length(trainSet{i,2});
    nInstances = nInstances + prior(i);
end
prior = prior./nInstances;
switch (caseIdx)
    case 1
        covariances=cell(nClasses,1);
        for i=1:nClasses
            covariances{i} = cov(trainSet{i,2});
        end
    case 2
        covariance = zeros(nFeatures,nFeatures);
        for i=1:nClasses
            covariance = covariance + cov(trainSet{i,2})*prior(i);
        end
        covariances = cell(nClasses,1);
        for i=1:nClasses
            covariances{i} = covariance;
        end
    case 3
        variance = zeros(nFeatures,nFeatures);
        for i=1:nClasses
            variance = variance + diag(var(trainSet{i,2})*prior(i));
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

