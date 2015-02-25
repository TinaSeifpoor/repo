classdef Downloader < handle
    %DOWNLOADER Summary of this class goes here
    %   Detailed explanation goes here
    properties(SetAccess = protected, GetAccess = public)
        objectNames
        destination
    end
    properties(SetAccess = public, GetAccess = public)
        timeout
    end
    properties(SetAccess = protected, GetAccess = protected)
        executable
    end    
    methods
        function DL = Downloader(destination, textToImagePath, timeout)
            if (nargin>0)
                DL.destination = destination;
            else
                DL.destination = './downloaderOutput/';
            end
            if (nargin>1)
                DL.executable = textToImagePath;
            else
                DL.executable = './TextToImage/TextToImage.exe';
            end
            if (nargin>2)
                DL.timeout = timeout;
            else
                DL.timeout = 20000;
            end
        end
        function addObject(DL, object)
            DL.objectNames{length(DL.objectNames)+1} = object;
        end
        function addObjects(DL, objects)
            DL.objectNames((length(DL.objectNames)+1):length(objects)) = objects;
        end
        function [fileList, objectList]=download(DL, appendObjectName)
            if (nargin<2)
                appendObjectName=true;
            end
            for idxObject = 1:numel(DL.objectNames)
                objectName = DL.objectNames{idxObject};
                if (appendObjectName)
                    destinationPath = strcat(DL.destination,'/', objectName, '/');
                end
                currentFileList = downloadSolo(objectName, destinationPath, DL.executable, DL.timeout);
                currentFileList = strcat(destinationPath, currentFileList);
                fileList(length(fileList)+1 : length(currentFileList)) = currentFileList;
                objectList(length(objectList)+1 : length(currentFileList)) = objectName;
            end
        end
    end
end
function fileList = downloadSolo(objectName, destinationPath, executable, timeout)
evalStr = ['!"' executable '" "' objectName '" "' destinationPath '" ' num2str(timeout)];
eval(evalStr);
fileList = getFileList(destinationPath);
end
function fileList = getFileList(path)
entryList=dir(path);
isubfile = ~cell2mat({entryList(:).isdir});
fileList = entryList(isubfile);
end

