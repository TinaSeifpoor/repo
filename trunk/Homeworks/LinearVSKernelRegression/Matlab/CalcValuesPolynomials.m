function [valuesP,error] = CalcValuesPolynomials(traDataset,valDataset,polyDegrees)
%CALCVALUESPOLYNOMIALS Calculates correspondences for validation dataset's 
%x-points using training dataset correspondences with polynomial approxim-
%ation. Returns predicted validation y-points and mean square error.
nPolyDegrees= numel(polyDegrees);
for idxPolyDegree = 1:nPolyDegrees
    polyDegree = polyDegrees(idxPolyDegree);
    p = polyfit(traDataset(:,1),traDataset(:,2),...
        polyDegree);
    datasetPred=polyval(p,valDataset(:,1));
    valuesP(idxPolyDegree,:)=datasetPred;
end
if (nargout>1)
    error = MeanSquaredError(valDataset,valuesP)';
end
end

function errorList = MeanSquaredError(dataset, valuesP)
%MEANSQUAREDERROR Calculates mean squared error
xRange = max(dataset(:,1))-min(dataset(:,1));
valuesR = repmat(dataset(:,2)',size(valuesP,1),1);
errorList = (mean((valuesP-valuesR).^2,2).^.5)./xRange;
end