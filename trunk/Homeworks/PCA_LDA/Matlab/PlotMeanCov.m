function [] = PlotMeanCov( means, covars, keyword )
%PLOTMEANCOV Plot mean and covariances with weighted gray values with their
%actualy values as text.

nMeans = size(means,3);
for idxMean=1:nMeans
    meanSelected = means(:,:,idxMean);
    PlotMean(meanSelected, [keyword 'Mean' num2str(idxMean)]);
end
nCovars = size(covars,1);
for idxCovar=1:nCovars
    covarSelected = covars{idxCovar};
    PlotCovar(covarSelected, [keyword 'Covar' num2str(idxCovar)]);
end
end

function [] = PlotMean( mat, filename)
h=figure;imagesc(mat);            %# Create a colored plot of the matrix values
pos = get(h, 'Position');
set(h, 'Position', [pos(1) pos(2) 250 150]);
set(gcf, 'PaperPositionMode','auto')
colormap(flipud(gray));  %# Change the colormap to gray (so higher values are
                         %#   black and lower values are white)

textStrings = num2str(mat(:),'%0.2f');  %# Create strings from the matrix values
textStrings = strtrim(cellstr(textStrings));  %# Remove any space padding
[x,y] = meshgrid(1:size(mat,2),1:size(mat,1));   %# Create x and y coordinates for the strings
hStrings = text(x(:),y(:),textStrings(:),...      %# Plot the strings
                'HorizontalAlignment','center');
midValue = mean(get(gca,'CLim'));  %# Get the middle value of the color range
textColors = repmat(mat(:) > midValue,1,3);  %# Choose white or black for the
                                             %#   text color of the strings so
                                             %#   they can be easily seen over
                                             %#   the background color
set(hStrings,{'Color'},num2cell(textColors,2));  %# Change the text colors

ylabel('Classes');xlabel('Means');
set(gca,'YTick',1:5,...                         %# Change the axes tick marks
        'YTickLabel',{'Class 1','Class 2','Class 3'},...  %#   and tick labels
        'XTick',1:5,...
        'XTickLabel',{'X1','X2'},...
        'TickLength',[0 0]);
saveas(gcf, filename, 'epsc');
close gcf;
end

function [] = PlotCovar(mat, filename)
h = figure;imagesc(mat);            %# Create a colored plot of the matrix values
pos = get(h, 'Position');
set(h, 'Position', [pos(1) pos(2) 150 100]);
set(gcf, 'PaperPositionMode','auto')
colormap(flipud(gray));  %# Change the colormap to gray (so higher values are
                         %#   black and lower values are white)

textStrings = num2str(mat(:),'%0.2f');  %# Create strings from the matrix values
textStrings = strtrim(cellstr(textStrings));  %# Remove any space padding
[x,y] = meshgrid(1:size(mat,2),1:size(mat,1));   %# Create x and y coordinates for the strings
hStrings = text(x(:),y(:),textStrings(:),...      %# Plot the strings
                'HorizontalAlignment','center');
midValue = mean(get(gca,'CLim'));  %# Get the middle value of the color range
textColors = repmat(mat(:) > midValue,1,3);  %# Choose white or black for the
                                             %#   text color of the strings so
                                             %#   they can be easily seen over
                                             %#   the background color
set(hStrings,{'Color'},num2cell(textColors,2));  %# Change the text colors

set(gca,'XTick',1:5,...                         %# Change the axes tick marks
        'YTickLabel',{'X1','X2'},...  %#   and tick labels
        'YTick',1:5,...
        'XTickLabel',{'X1','X2'},...
        'TickLength',[0 0]);
saveas(gcf, filename, 'epsc');
close gcf;
end
