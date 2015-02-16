function [ h ] = reportLogprob( mat, filename)
%REPORTLOGPROB Plot Log probabilities
h = figure;imagesc(mat);            %# Create a colored plot of the matrix values
pos = get(h, 'Position');
[nRows, nCols] = size(mat);
set(h, 'Position', [pos(1) pos(2) nCols*55  nRows*20]);
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
colStep = nCols/3;
set(gca,'XTick',(1+colStep)/2:colStep:nCols-(1+colStep)/2+1,... %# Change the axes tick marks
        'XTickLabel', ['Log Likelihoods for N=2';'Log Likelihoods for N=3';'Log Likelihoods for N=5'],...
        'YTick', 2:4:50,...
        'TickLength',[0 0]);
saveas(gcf, filename, 'psc2');
end

