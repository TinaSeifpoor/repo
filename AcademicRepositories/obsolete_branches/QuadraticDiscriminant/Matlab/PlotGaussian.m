function [im] = PlotGaussian( mu ,s)
%PLOTGAUSSIAN Plots likelihoods
im = zeros(80,100);
for x1Ind=1:80
    x1 = (x1Ind-1)/8;
    for x2Ind = 1:100
        x2 = (x2Ind-1)/14-2;
        im(x1Ind,x2Ind) = gaussian_dist([x1 x2],mu,s);
    end
end
im = im./sum(sum(im));
end

function f = gaussian_dist (x, mu, s)
d = size(x,2);
p1 = (2*pi)^(d/2) * det(s)^0.5;
p2 = exp(-0.5 * ((x-mu)*inv(s)*(x-mu)'));
f = p2 / p1;
end