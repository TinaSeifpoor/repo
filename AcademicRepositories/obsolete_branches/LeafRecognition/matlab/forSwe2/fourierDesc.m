function [ output_args ] = fourierDesc( input_args )
%FOURIERDESC Summary of this function goes here
%   Detailed explanation goes here
%         [a,b] = max(sum(regLeafNorm==1));
%         c = find(regLeafNorm(:,811)==1, 1, 'last' );
%         point = [b,c];
%         leafBound = bwboundaries(regLeafNorm);
%         pointsLeafBound = leafBound{1};
%         %% Align it to point
% %         find((pointsLeafBound(:,1)==point(1,1)).*(pointsLeafBound(:,2)==point(1,2))1)
        %% Get Chain Code
%         nPoints = size(pointsLeafBound,1);
%         pointsLeafBoundPushed = pointsLeafBound(2:nPoints,:);
%         pointsLeafBoundPulled = pointsLeafBound(1:nPoints-1,:);
%         steps = pointsLeafBoundPushed-pointsLeafBoundPulled;
%         chainCode = zeros(size(steps,1),1);
%         for idxStep = 1:size(steps,1)
%             step = steps(idxStep,:);
%             if (step==[1,0])
%                 cc = 0;
%             elseif (step==[1,-1])
%                 cc = 1;
%             elseif (step==[0,-1])
%                 cc = 2;
%             elseif (step==[-1,-1])
%                 cc = 3;
%             elseif (step==[-1,0])
%                 cc = 4;
%             elseif (step==[-1,1])
%                 cc = 5;
%             elseif (step==[0,1])
%                 cc = 6;
%             elseif (step==[1,1])
%                 cc = 7;
%             end
%             chainCode(idxStep) =cc;
%         end

end

