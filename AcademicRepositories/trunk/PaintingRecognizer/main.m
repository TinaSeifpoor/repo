clear; clc; close all;
% init
load('resume');
load('seed');
rng(s);
addpath('../libsvm-3.20/matlab/');
%% Train SVM
samples = e.samples;
[centuryNames, ~, centuries] = unique({samples(:).class});
[genderNames, ~, genders] = unique({samples(:).base});
mixClass = (genders-1)*numel(centuryNames)+centuries;
% correspondences = [mixClass, genders, centuries];

X = e.layerX{1};
tList = [350,450,550];
yList = [centuries,genders,mixClass];
resultCount = cell(size(yList,2),numel(tList));
resultPerce = cell(size(yList,2),numel(tList));
for idxY=1:size(yList,2)
    for idxT=1:numel(tList)
        currentResult=performValidation(X,yList(:,idxY),tList(idxT));
        resultCount{idxY,idxT} = currentResult.valid.confusion;
        resultPerce{idxY,idxT} = bsxfun(@rdivide,currentResult.valid.confusion, sum(currentResult.valid.confusion));
    end
end
displayValidation(resultPerce{1,:});
save('results', 'resultCount', 'resultPerce')