function sequenceIdx = genSequence (varargin)
if (nargin==1)
  varargin = varargin{1};
end
  rolls = varargin{1};
  probCell = varargin(2:end);
  nDepth = length(probCell);
  sequenceIdx = [];
  for idxElement=1:length(rolls)
    argIdx = min(nDepth,idxElement);
    prob = probCell{argIdx};
    if (argIdx>1)
      currentSequenceIdx = sequenceIdx(end-argIdx+2:end);
      probSelectionText = ['prob = squeeze(prob('];
      for i = 1:length(currentSequenceIdx)
        probSelectionText = [probSelectionText num2str(currentSequenceIdx(i)) ','];
      end
      probSelectionText = [probSelectionText ':));'];
      eval(probSelectionText);
    end
    if (size(prob,1) > size(prob,2))
      prob = prob';
    end
    sequenceIdx(idxElement) = predictNext(rolls(idxElement),prob);
  end
end

function nextIdx = predictNext (roll,probability)
  probability = probability/sum(probability);
  probability = cumsum(probability);
  probability = [0,probability];
  nextIdx = min(max(find(roll>probability))+1,length(probability))-1;
  if (isempty(nextIdx))
    display(roll)
    display(probability)
  end
end
