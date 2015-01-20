function Categorizer = downloadSamples(textToImagePath, Categorizer)
%DOWNLOADSAMPLES Summary of this function goes here
%   Detailed explanation goes here
for i=1:numel(Categorizer.className)
    evalStr = ['!"' textToImagePath.bin '" ' Categorizer.className{i} ' ' textToImagePath.dir ' 20000'];
    eval(evalStr);
end
[Categorizer.imageFile, Categorizer.className, ~] = getimagefiles(textToImagePath.dir);
[~,~,Categorizer.classIndex] = unique(Categorizer.className);
end

