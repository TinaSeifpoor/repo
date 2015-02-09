function [imageFileList,baseDirNames,baseFileNames] = getimagefiles(path, dirName, appPath)
%GETIMAGEFILES Summary of this function goes here
%   Detailed explanation goes here
if (isempty(path))
    imageFileList = {};
    return;
end
if (nargin==3)
    entryList = dir(strcat(path,appPath));
else
    entryList = dir(path);
end
if (nargin==1)
    isubdir = [entryList(:).isdir];
    entryList = entryList(isubdir);
    isubdir = [entryList(:).isdir];
else
    isubdir = [entryList(:).isdir];
end
isubfile = ~isubdir;
entryNameList = {entryList(:).name};
isubfile(ismember(entryNameList,{'.','..'})) = 0;
isubdir(ismember(entryNameList,{'.','..'})) = 0;
if (nargin==3)
    entryPathList = strcat(appPath,entryNameList);
else
    entryPathList = entryNameList;
end
dirList = entryPathList(isubdir);
dirList = strcat(dirList,'/');
imageFileList = entryPathList(isubfile);
if (nargin>1)
    baseDirNames = repmat({dirName},1,numel(imageFileList));
else
    baseDirNames = repmat({'-1'},1,numel(imageFileList));
end
baseFileNames = entryNameList(isubfile);
childDirNames = entryNameList(isubdir);
for i=1:numel(dirList)
    if (nargin==3)
        [subdirImageFileList, subdirBaseDirNames, subdirBaseFileNames]= getimagefiles(path,childDirNames{i},strcat(appPath,dirList{i}));    
    else
        [subdirImageFileList, subdirBaseDirNames, subdirBaseFileNames]= getimagefiles(path,childDirNames{i},dirList{i});
    end
    imageFileList = [imageFileList subdirImageFileList{:}]; %#ok<AGROW>
    baseDirNames = [baseDirNames subdirBaseDirNames{:}]; %#ok<AGROW>
    baseFileNames = [baseFileNames subdirBaseFileNames{:}]; %#ok<AGROW>
end
end
