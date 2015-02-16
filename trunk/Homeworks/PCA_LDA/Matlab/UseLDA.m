function [ldaVectors] = UseLDA(featureList, classList, n, filename)
%USELDA Reduces number of dimensions to n
if (size(featureList,2)<=n)
    ldaVectors = eye(size(featureList,2));
    return;
end
nClasses = numel(unique(classList));
featureList = NormalizeFeatures(featureList);

[means, covariances, priors] = CalculateParameters(featureList, classList ,1);
Sw = 0;
for idxClass = 1:nClasses
    classCov = covariances{idxClass};
    classPri = priors(idxClass);
    Sw = Sw + classCov*classPri;
end
generalMean = mean(means,1);
Sb = 0;
for idxClass = 1:nClasses
    classMean = means(idxClass,:);
    Sb = Sb + (classMean-generalMean)'*(classMean-generalMean);
end
trans = inv(Sw)*Sb;
[V,D] = eig(trans);
eigVals = diag(D);
[~, idxOrder] = sort(eigVals,'descend');
idxSelected = idxOrder(1:n);
ldaVectors = V(:,idxSelected);
if (nargin == 4)
    PlotTransformation(ldaVectors, filename);
end
end

function [featureListOut] = NormalizeFeatures(featureList)
%NORMALIZEFEATURES Shifts features to zero mean
featureMeans = mean(featureList,1);
featureListOut = bsxfun(@minus,featureList,featureMeans);
end
