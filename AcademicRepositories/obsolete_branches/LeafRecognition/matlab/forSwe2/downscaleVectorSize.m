function varargout = downscaleVectorSize(varargin)
%DOWNSCALEVECTORSIZE Summary of this function goes here
%   Detailed explanation goes here

k = varargin{1};
varargout = cell(nargin-1,1);
for i=2:nargin
    vec = varargin{i};
    scaleRatio = size(vec,1)/k;
    idxScale = round(1:scaleRatio:size(vec,1));
    if (numel(unique(idxScale)) == k)
        vecOut = vec(idxScale);
    else
        warning('Did not work!!');
    end
    varargout{i-1} = vecOut;
end
end

