function [] = DispFits(perf, dataset, parList, keyword)
%DISPFITS Displays mean squared error per parameter and with best fit,
%over-fit and under-fit results.
[perfMean, fitListIdx] = PostProcessRegression(perf);
figure;plot(perfMean);
pos = get(gcf, 'Position');
set(gcf, 'Position', [pos(1) pos(2) 600 300]);
ylim([0.1 0.5]);
xlim([1 numel(perfMean)]);
set(gca,'XTick',1:numel(parList));
set(gca,'XTickLabel',num2str(parList(:),3));
text(fitListIdx(1),perfMean(fitListIdx(1)),...
    ['\uparrow Minimum (' num2str(perfMean(fitListIdx(1)),3)...
    ')\newline @ ' keyword ' = ' num2str(parList(fitListIdx(1)))],...
     'VerticalAlignment','top','HorizontalAlignment','left');
xlabel(keyword);
ylabel('Mean squared error');
saveas(gcf, [keyword '-MeanSquareError.eps'],'psc2');
%%
[valuesX,sortIdx] = sort(dataset(:,1));
valuesY = dataset(:,2);
valuesY = valuesY(sortIdx);
%%
if (keyword=='h')
    valuesP = CalcValuesKernel([valuesX,valuesY], valuesX, parList(fitListIdx));
else
    valuesP = CalcValuesPolynomials([valuesX,valuesY], valuesX, parList(fitListIdx));
end
valuesYFit = valuesP(1,:);
valuesYUnderFit = valuesP(2,:);
valuesYOverFit = valuesP(3,:);
figure;hold on;
plot(valuesX, valuesY,'kx');
plot(valuesX, valuesYFit,'r');
plot(valuesX, valuesYUnderFit,'g');
plot(valuesX, valuesYOverFit,'b');
legend('Dataset',...
    [keyword '=' num2str(parList(fitListIdx(1)),2)],...
    [keyword '=' num2str(parList(fitListIdx(2)),2)],...
    [keyword '=' num2str(parList(fitListIdx(3)),2)]);
xlabel('x');
ylabel('y');
xlim([min(valuesX), max(valuesX)]);
saveas(gcf, [keyword '-Fits.eps'],'psc2');
end

function [perfMean, fitIdx] = PostProcessRegression(perf)
%POSTPROCESSREGRESSION Returns mean performance for each parameter and best
%fit, under fit and over fit parameter indices to plot.
perfMean = trimmean(perf,20);
%%
[~, fitIdx] = min(perfMean);
underFitIdx = 1;
overFitIdx = size(perf,2);
fitIdx = [fitIdx, underFitIdx, overFitIdx];
end

