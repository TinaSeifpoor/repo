function [INDICES] = mycrossvalind(N,K)
%MYCROSSVALIND Generates K folds for N observations with equal 
%observations in each fold (omits excess data).
nObservations = size(N,1);
nObservationsPerFold = nObservations/K;
idxObsIndexN = 1:nObservations;
INDICES = zeros(nObservations,1);

for idxFold = 1:K
    for idxObsIndexPicked = 1:nObservationsPerFold
        idxObsIndexNPicked = uint32(rand(1)*(numel(idxObsIndexN)-1))+1;
        INDICES(idxObsIndexN(idxObsIndexNPicked))=idxFold;
        idxObsIndexN(idxObsIndexNPicked)=[];
    end
end
end

