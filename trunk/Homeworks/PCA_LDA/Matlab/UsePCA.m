function [pcaVectors] = UsePCA(featureList,n, filename)
%USEPCA Reduces number of dimensions to n
if (size(featureList,2)<=n)
    pcaVectors = eye(size(featureList,2));
    return;
end
featureList = NormalizeFeatures(featureList);
covFeatures = cov(featureList);
[V,D] = eig(covFeatures);
eigVals = diag(D);
[~, idxOrder] = sort(eigVals,'descend');
idxSelected = idxOrder(1:n);
pcaVectors = V(:,idxSelected);
if (nargin==3)
    PlotTransformation(pcaVectors, filename);
end
end

function [featureListOut] = NormalizeFeatures(featureList)
%NORMALIZEFEATURES Shifts features to zero mean
featureMeans = mean(featureList,1);
featureListOut = bsxfun(@minus,featureList,featureMeans);
end