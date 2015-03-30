function model = libsvmtrain(X,y)
%LIBSVMTRAIN Summary of this function goes here
%   Detailed explanation goes here
model.mean = mean(X);
X_meanFixer = repmat(-model.mean, size(X,1), 1);
X_zmean = X + X_meanFixer;
model.std  = sqrt(var(X_zmean));
X_varFixer = repmat(1./model.std, size(X,1), 1);
X_norm = X_zmean.*X_varFixer;
tic
model.m = svmtrain(y,double(X_norm), '-b 1 -t 0 -q');
toc
end

