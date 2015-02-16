function [] = PlotResults(means, covariances)
%PLOTRESULTS Plots 3-D Posteriors and Likelihoods
im1= PlotGaussian(means(1,:),covariances{1});
im2= PlotGaussian(means(2,:),covariances{2});
im3= PlotGaussian(means(3,:),covariances{3});
x1List = (1:size(im1,1))/8;
x2List = (1:size(im1,2))/14-2;
%% Likelihoods
minLikelihood = 0; maxLikelihood = max(max(max(cat(3,im1',im2',im3'),[],3)))*1.2;
figure;h = surf(x1List,x2List,im1');xlabel ('x1');ylabel ('x2');zlabel ('Likelihood of C1');zlim([minLikelihood,maxLikelihood])
figure;surf(x1List,x2List,im2');xlabel ('x1');ylabel ('x2');zlabel ('Likelihood of C2');zlim([minLikelihood,maxLikelihood])
figure;surf(x1List,x2List,im3');xlabel ('x1');ylabel ('x2');zlabel ('Likelihood of C3');zlim([minLikelihood,maxLikelihood])
%% Posteriors
figure; surf(x1List,x2List,((im1 > im2) .* (im1 > im3))');xlabel ('x1');ylabel ('x2');zlabel ('P(C1|X)');
figure; surf(x1List,x2List,((im2 > im1) .* (im2 > im3))');xlabel ('x1');ylabel ('x2');zlabel ('P(C2|X)');
figure; surf(x1List,x2List,((im3 > im2) .* (im3 > im1))');xlabel ('x1');ylabel ('x2');zlabel ('P(C3|X)');
end

