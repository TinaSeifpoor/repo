function trimMean= TrimMean(matrix, dim, perc)
%TRIMMEAN Omits largest and smallest perc percent elements and calculates
%means of the remaining values in matrix in dimension dim (dim=1 in 2-D
%matrix trims and calculates means on each column and then |trimMean| = #
%of cols; vice-versa |trimMean| = # of rows on dim=2)

%If called with no parameters, dim = 1 and perc = 10%

if(nargin<2)
    dim = 1;
end
if(nargin<3)
    perc=0.1;
end

lengthDim = size(matrix,dim);
nTrim = ceil(perc*lengthDim); %#ok<NASGU>
trimSort = sort(matrix,dim);
%% omit first nTrim elements AND last nTrim elements from the matrix in 
% dimension dim
nDim = numel(size(matrix));
strIdxToOmit='[1:nTrim,lengthDim-nTrim+1:lengthDim]';
strIdx = [repmat(sprintf(':,'),1,dim-1) strIdxToOmit repmat(sprintf(',:'),1,nDim-dim)];
strEval = ['trimSort(' strIdx ')=[];'];
eval(strEval);
trimMean=mean(trimSort,dim);

end

