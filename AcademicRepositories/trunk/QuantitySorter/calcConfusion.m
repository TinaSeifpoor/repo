function confusion = calcConfusion(yPredict, yActual)
%CALCCONFUSÝON Summary of this function goes here
%   Detailed explanation goes here
nClass = numel(unique(yActual));
confusion = zeros(nClass);
for idxPredict=1:nClass
    idxSamplePredict = yPredict==idxPredict;
    for idxActual=1:nClass
        currentActual = yActual(idxSamplePredict);
        idxSamplePredictActual = currentActual==idxActual;
        confusion(idxPredict,idxActual) = length(find(idxSamplePredictActual));
    end
end
end

