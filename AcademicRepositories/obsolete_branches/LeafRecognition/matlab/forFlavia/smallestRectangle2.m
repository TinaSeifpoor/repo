function [ rect2 ] = smallestRectangle2( reg )
%MINIMUMAREAENCLOSINGRECTANGLE Summary of this function goes here
%   Detailed explanation goes here
[rowList, colList] = find(reg);
points = extremePoints(rowList, colList);
% realTopLeftCorner = [points(2,1),points(4,2)];
% realTopRightCorner = [points(2,1), points(3,2)];
% realBottomLeftCorner = [points(1,1), points(4,2)];
% realBottomRightCorner = [points(1,1), points(3,2)];
% imshow(reg);hold on;plot(...
%     [realTopLeftCorner(2),realTopRightCorner(2),realBottomRightCorner(2),realBottomLeftCorner(2),realTopLeftCorner(2)],...
%     [realTopLeftCorner(1),realTopRightCorner(1),realBottomRightCorner(1),realBottomLeftCorner(1),realTopLeftCorner(1)]...
%     ,'--rs');hold off;
minArea = inf;
rect2 = zeros(4,1);
%
for i=1:3
    for j=i+1:4
        phi = calcLineAngle(points(i,:), points(j,:));
        R = calcRotationMatrix (-phi);
        RTform = maketform('affine', R);
        tPoints = tforminv(RTform, [rowList,colList]);
        tPoints = extremePoints(tPoints(:,1),tPoints(:,2));
        width = abs(tPoints(1,1) - tPoints(2,1));
        height = abs(tPoints(3,2) - tPoints(4,2));
        area = width*height;
        if (area < minArea)
            minArea = area;
            tTopLeftCorner = [tPoints(2,1),tPoints(4,2)];
            topLeftCorner = tformfwd(RTform, tTopLeftCorner);
            %             tTopRightCorner = [tPoints(2,1), tPoints(3,2)];
            %             topRightCorner = tformfwd(RTform, tTopRightCorner);
            %             tBottomRightCorner = [tPoints(1,1), tPoints(3,2)];
            %             bottomRightCorner = tformfwd(RTform, tBottomRightCorner);
            %             tBottomLeftCorner = [tPoints(1,1), tPoints(4,2)];
            %             bottomLeftCorner = tformfwd(RTform, tBottomLeftCorner);
            %             figure;plot(...
            %     [tTopLeftCorner(2),tTopRightCorner(2),tBottomRightCorner(2),tBottomLeftCorner(2),tTopLeftCorner(2)],...
            %     [tTopLeftCorner(1),tTopRightCorner(1),tBottomRightCorner(1),tBottomLeftCorner(1),tTopLeftCorner(1)]...
            %     ,'--rs');
            %             figure;imshow(reg);hold on;plot([topLeftCorner(2),topRightCorner(2),bottomRightCorner(2),bottomLeftCorner(2),topLeftCorner(2)],[topLeftCorner(1),topRightCorner(1),bottomRightCorner(1),bottomLeftCorner(1),topLeftCorner(1)],'--rs');hold off;
            rect2 = [topLeftCorner,width,height,phi];
        end
    end
end
end

function [points] = extremePoints(xList,yList)
[~, xMaxInd] = max(xList); [~, xMinInd] = min(xList); [~, yMaxInd] = max(yList); [~, yMinInd] = min(yList);
points = zeros(4,2);
[points(1,:)] = [xList(xMaxInd), yList(xMaxInd)];
[points(2,:)] = [xList(xMinInd), yList(xMinInd)];
[points(3,:)] = [xList(yMaxInd), yList(yMaxInd)];
[points(4,:)] = [xList(yMinInd), yList(yMinInd)];

end

function [phi] = calcLineAngle (points1, points2)
if (points1==points2)
    phi=0;
else
    phi = atan((points1(2) - points2(2)) / (points1(1) - points2(1)));
end
end

function [R] = calcRotationMatrix (phi)
R = zeros(3);
R(1,1) = cos(phi); R(1,2) = -sin(phi);
R(2,1) = sin(phi); R(2,2) = cos(phi);
R(3,3) = 1;
end