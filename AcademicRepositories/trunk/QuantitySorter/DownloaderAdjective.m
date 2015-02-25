classdef DownloaderAdjective < handle
    %DOWNLOADERADJECTIVE Summary of this class goes here
    %   Detailed explanation goes here
    
    properties(SetAccess = protected, GetAccess = public)
        objects
        adjectiveNames
        baseNames
        destination
    end
    properties(SetAccess = public, GetAccess = public)
        timeout
    end
    properties(SetAccess = protected, GetAccess = protected)
        executable
    end    
    
    methods    
        function addAdjective(DL, adjective)
            DL.adjectiveNames{length(DL.adjectiveNames)+1} = adjective;
        end
        function addAdjectives(DL, adjectives)
            DL.adjectiveNames((length(DL.adjectiveNames)+1):length(adjectives)) = adjectives;
        end
        function addBase(DL, base)
            DL.baseNames{length(DL.baseNames)+1} = base;
        end
        function addBases(DL, bases)
            DL.baseNames((length(DL.baseNames)+1):length(bases)) = bases;
        end
        function updateObjectNames(DL)
            classNameBtw   = repmat({' '},size(DL.adjectiveNames,2),size(DL.baseNames,2));
            DL.objects.adjectives = repmat(DL.adjectiveNames',1,size(DL.baseNames,2));
            DL.objects.bases = repmat(DL.baseNames,size(DL.adjectiveNames,2),1);
            DL.objects.names = strcat(DL.objects.adjectives, classNameBtw, DL.objects.bases);
            DL.objects.destinations = strcat(DL.destination, '/', DL.objects.adjectives);
        end
        function out=download(DL, isFake)
            if (nargin<2)
                isFake=false;
            end
            if (isempty(DL.objects))
                DL.updateObjectNames;
            end
            fileList=cell(0);
            baseList=cell(0);
            adjectiveList=cell(0);
            for idxObject = 1:numel(DL.objects.names)
                objectName = DL.objects.names{idxObject};
                objectDestination = DL.objects.destinations{idxObject};
                objectAdjective = DL.objects.adjectives{idxObject};
                objectBase = DL.objects.bases{idxObject};
                if (~isFake)
                    downloadSolo(objectName, objectDestination, DL.executable, DL.timeout);
                end
                objectFileList = strcat(objectDestination, '/', getFileList(objectDestination));
                fileList(length(fileList)+1 : length(fileList)+length(objectFileList)) = objectFileList(:);
                baseList(length(baseList)+1 : length(baseList)+length(objectFileList)) = {objectBase};
                adjectiveList(length(adjectiveList)+1 : length(adjectiveList)+length(objectFileList)) = {objectAdjective};
            end
            out = cell2struct([fileList;adjectiveList;baseList], {'path', 'class', 'base'});
        end
        function DL = DownloaderAdjective(destination, textToImagePath, timeout)
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
    end
end
function fileList = downloadSolo(objectName, destinationPath, executable, timeout)
evalStr = ['!"' executable '" "' objectName '" "' destinationPath '" ' num2str(timeout)];
eval(evalStr);
end
function fileList = getFileList(path)
entryList=dir(path);
isubfile = ~cell2mat({entryList(:).isdir});
fileList = {entryList(isubfile).name};
end


