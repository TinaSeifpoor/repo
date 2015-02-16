function [valuesP, error] = CalcValuesKernel(traDataset, valDataset, hList)
%CALCVALUESKERNEL Calculates correspondences for validation dataset's x-
%points using training dataset correspondences with kernel regression. 
%Returns predicted validation y-points and mean square error.
valuesP = zeros(numel(hList),size(valDataset,1));
for idxH=1:numel(hList)
    h = hList(idxH);
    xMat1 = repmat(traDataset(:,1)',size(valDataset,1),1);
    xMat2 = repmat(valDataset(:,1)',size(traDataset,1),1)';
    weightMat = exp(-abs(xMat1-xMat2).^2/h.^2);
    yMat1 = repmat(traDataset(:,2)',size(valDataset,1),1);
    valuesP(idxH,:) = sum(yMat1.*weightMat,2)./sum(weightMat,2);
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