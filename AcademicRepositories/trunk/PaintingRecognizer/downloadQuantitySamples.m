function []= downloadQuantitySamples(TextToImagePath, adjectiveName, objectName)
%DOWNLOADQUANTÝTYSAMPLES Summary of this function goes here
%   Detailed explanation goes here
classNameBtw   = repmat({' '},size(adjectiveName,2),size(objectName,2));
adjectiveNames = repmat(adjectiveName',1,size(objectName,2));
objectNames    = repmat(objectName,size(adjectiveName,2),1);

classNames = strcat(adjectiveNames, classNameBtw, objectNames);

for idxAdj = 1:size(classNames,1)
    TextToImagePathForAdj = TextToImagePath;
    TextToImagePathForAdj.dir = [TextToImagePathForAdj.dir,adjectiveName{idxAdj}];
    downloadSamples(TextToImagePathForAdj,classNames(idxAdj,:));
end
end

