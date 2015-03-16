function [idxList, prob] = libsvmpredict(model, X, nResults)
%LIBSVMPREDICT Summary of this function goes here
%   Detailed explanation goes here
X_norm = (X-model.minX) / ((model.maxX-model.minX) / 2) - 1;
y = ones(size(X_norm,1),1);
[~,~,t3] = svmpredict(y,double(X_norm), model.m,'-b 1');
probabilities = t3(:,1);
[prob, idxList] = sort(probabilities,'descend');
if(nargin>2)
    if (numel(prob)>nResults)
        prob = prob(1:nResults);
        idxList = idxList(1:nResults);
    end
end
end

