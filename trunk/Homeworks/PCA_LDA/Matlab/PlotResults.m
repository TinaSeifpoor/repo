function [x1ListOut, x2ListOut] = PlotResults(means, covariances, keyword, x1List, x2List)
%PLOTRESULTS Plots 3-D Posteriors and Likelihoods
if (nargin==3)
    sigma = 3; nSamples = 200;
    variances = zeros(numel(covariances),2);
    for i=1:numel(covariances)
        variances(i,:) = diag(covariances{i});
    end
    %
    minList = means-sigma*variances;
    maxList = means+sigma*variances;
    xMin = min(minList);
    xMax = max(maxList);
    xStep = (xMax-xMin) / nSamples;
    x1ListOut = xMin(1):xStep(1):xMax(1);
    x2ListOut = xMin(2):xStep(2):xMax(2);
else
    x1ListOut = x1List;
    x2ListOut = x2List;
end
PlotMeanCov(means, covariances, keyword);
[im1] = PlotGaussian(means(1,:),covariances{1}, x1ListOut, x2ListOut);
[im2] = PlotGaussian(means(2,:),covariances{2}, x1ListOut, x2ListOut);
[im3] = PlotGaussian(means(3,:),covariances{3}, x1ListOut, x2ListOut);

%% Likelihoods
minLikelihood = 0; maxLikelihood = max(max(max(cat(3,im1',im2',im3'),[],3)))*1.2;
figure;surf(x1ListOut,x2ListOut,im1');xlabel ('x1');ylabel ('x2');zlabel ('Likelihood of C1');zlim([minLikelihood,maxLikelihood])
saveas(gcf, [keyword 'LC1'], 'epsc');close gcf;
figure;surf(x1ListOut,x2ListOut,im2');xlabel ('x1');ylabel ('x2');zlabel ('Likelihood of C2');zlim([minLikelihood,maxLikelihood])
saveas(gcf, [keyword 'LC2'], 'epsc');close gcf;
figure;surf(x1ListOut,x2ListOut,im3');xlabel ('x1');ylabel ('x2');zlabel ('Likelihood of C3');zlim([minLikelihood,maxLikelihood])
saveas(gcf, [keyword 'LC3'], 'epsc');close gcf;
%% Posteriors
figure; surf(x1ListOut,x2ListOut,((im1 > im2) .* (im1 > im3))');xlabel ('x1');ylabel ('x2');zlabel ('P(C1|X)');
saveas(gcf, [keyword 'PC1'], 'epsc');close gcf;
figure; surf(x1ListOut,x2ListOut,((im2 > im1) .* (im2 > im3))');xlabel ('x1');ylabel ('x2');zlabel ('P(C2|X)');
saveas(gcf, [keyword 'PC2'], 'epsc');close gcf;
figure; surf(x1ListOut,x2ListOut,((im3 > im2) .* (im3 > im1))');xlabel ('x1');ylabel ('x2');zlabel ('P(C3|X)');
saveas(gcf, [keyword 'PC3'], 'epsc');close gcf;
end

