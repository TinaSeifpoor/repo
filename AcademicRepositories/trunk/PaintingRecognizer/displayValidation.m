function displayValidation(varargin)
%DÝSPLAYVALÝDATÝON Summary of this function goes here
%   Detailed explanation goes here
if (nargin>1)
    for i=1:nargin
       displaySingle(varargin{i}); 
    end
elseif(nargin==1)
    in = varargin{1};
    for i=1:numel(in)
        displaySingle(in{i});
    end
end
end


function displaySingle(res)
    figure;imagesc(res);
end
