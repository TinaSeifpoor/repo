function [ datasetOut ] = modifyDataset( dataset, nFiles )
%MODIFYDATASET Summary of this function goes here
%   Detailed explanation goes here
datasetOut = cell(size(dataset));
for i=1:numel(dataset)
    fileList = dataset{i};
    newFileList = fileList(1:nFiles);
    datasetOut{i} = newFileList;
end
end

