clear; clc; close all;
% init
load('resume');
addpath('../libsvm-3.20/matlab/');
%% Train SVM
samples = e.samples;
[centuryNames, ~, centuries] = unique({samples(:).class});
[genderNames, ~, genders] = unique({samples(:).base});
mixClass = (genders-1)*numel(centuryNames)+centuries;
% correspondences = [mixClass, genders, centuries];

X = e.layerX{1};
tList = [250, 300, 350];

for idxT=1:numel(tList)
    t = tList(idxT);
    result.gender    = performValidation(X, genders, t);
    result.century   = performValidation(X, centuries, t);
    result.mix       = performValidation(X, mixClass, t);
    results(idxT) = result;
end
save('results', 'results')