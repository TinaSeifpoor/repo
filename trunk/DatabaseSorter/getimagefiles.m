function [imageFileList,baseDirNames,baseFileNames] = getimagefiles(path, dirName)
%GETIMAGEFILES Summary of this function goes here
%   Detailed explanation goes here
if (isempty(path))
    imageFileList = {};
    return;
end
entryList = dir(path);
isubdir = [entryList(:).isdir];
isubfile = ~isubdir;
entryNameList = {entryList(:).name};
isubfile(ismember(entryNameList,{'.','..'})) = 0;
isubdir(ismember(entryNameList,{'.','..'})) = 0;
entryPathList = strcat(path,entryNameList);
dirList = entryPathList(isubdir);
dirList = strcat(dirList,'/');
imageFileList = entryPathList(isubfile);
if (nargin==2)
    baseDirNames = repmat({dirName},1,numel(imageFileList));
else
    baseDirNames = {};
end
baseFileNames = entryNameList(isubfile);
childDirNames = entryNameList(isubdir);
for i=1:numel(dirList)
    [subdirImageFileList, subdirBaseDirNames, subdirBaseFileNames]= getimagefiles(dirList{i},childDirNames{i});
    imageFileList = [imageFileList subdirImageFileList{:}]; %#ok<AGROW>
    baseDirNames = [baseDirNames subdirBaseDirNames{:}]; %#ok<AGROW>
    baseFileNames = [baseFileNames subdirBaseFileNames{:}]; %#ok<AGROW>
end
end
