function [ dataset ] = parseDataset( datasetPath )
%PARSEDATASET Summary of this function goes here
%   Detailed explanation goes here
datasetFolders = dir(datasetPath);
folderCount = 0;
dataset=cell(numel(datasetFolders)-2,1);
for i=1:numel(datasetFolders)
    folderInfo = datasetFolders(i);
    if (strcmp(folderInfo.name,'.') ||(strcmp(folderInfo.name,'..')))
        continue
    end
    folderCount = folderCount+1;
    fileInfos = dir([datasetPath folderInfo.name '/*.tif']);
    fileCount = 0;
    clear a;
    for j=1:numel(fileInfos)
        fileInfo = fileInfos(j);
        filename = fileInfo.name;
        if (~numel(regexp(filename,'-')))
            fileCount = fileCount+1;
            a{fileCount} = [datasetPath folderInfo.name '/' fileInfo.name];
        end
    end
    dataset{folderCount} = a;
end

end

