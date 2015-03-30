function classIndices = libsvmpredict(model, X)
%LIBSVMPREDICT Summary of this function goes here
%   Detailed explanation goes here
X_meanFixer = repmat(-model.mean, size(X,1), 1);
X_zmean = X + X_meanFixer;
X_varFixer = repmat(1./model.std, size(X,1), 1);
X_norm = X_zmean.*X_varFixer;
y = ones(size(X_norm,1),1);
[classIndices,~,~] = svmpredict(y,double(X_norm), model.m,'-b 1 -q');
end