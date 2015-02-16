function [im] = PlotGaussian( mu ,s, x1List, x2List)
%PLOTGAUSSIAN Plots likelihoods
im = zeros(numel(x1List),numel(x2List));
for x1Ind=1:numel(x1List)
    x1 = x1List(x1Ind);
    for x2Ind = 1:numel(x2List)
        x2 = x2List(x2Ind);
        im(x1Ind,x2Ind) = gaussian_dist([x1 x2],mu,s);
    end
end
%Normalize
im = im./sum(sum(im));
end

function f = gaussian_dist (x, mu, s)
d = size(x,2);
p1 = (2*pi)^(d/2) * det(s)^0.5;
p2 = exp(-0.5 * ((x-mu)*inv(s)*(x-mu)'));
f = p2 / p1;
end