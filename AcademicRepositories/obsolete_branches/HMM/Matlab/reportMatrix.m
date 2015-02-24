function [ h ] = reportMatrix( mat, labels, filename)
%REPORTLOGPROB Plot Log probabilities
h = figure;imagesc(mat);            %# Create a colored plot of the matrix values
pos = get(h, 'Position');
[nRows, nCols] = size(mat);
if (nRows > 1)
    set(h, 'Position', [pos(1) pos(2) nCols*55  nRows*25]);
else
    set(h, 'Position', [pos(1) pos(2) nCols*55  40]);
end
set(gcf, 'PaperPositionMode','auto')
colormap(flipud(gray));  %# Change the colormap to gray (so higher values are
                         %#   black and lower values are white)

textStrings = num2str(mat(:),'%0.2f');  %# Create strings from the matrix values
textStrings = strtrim(cellstr(textStrings));  %# Remove any space padding
% textStrings = strcat(cellstr(textStrings),'%');
[x,y] = meshgrid(1:size(mat,2),1:size(mat,1));   %# Create x and y coordinates for the strings
hStrings = text(x(:),y(:),textStrings(:),...      %# Plot the strings
                'HorizontalAlignment','center');
midValue = mean(get(gca,'CLim'));  %# Get the middle value of the color range
textColors = repmat(mat(:) > midValue,1,3);  %# Choose white or black for the
                                             %#   text color of the strings so
                                             %#   they can be easily seen over
                                             %#   the background color
set(hStrings,{'Color'},num2cell(textColors,2));  %# Change the text colors
set(gca,'XTick',1:nCols,... %# Change the axes tick marks
        'XTickLabel', labels.X,...
        'YTick',1:nRows,...
        'YTickLabel', labels.Y,...
        'TickLength',[0 0]);
saveas(gcf, filename, 'psc2');
end

