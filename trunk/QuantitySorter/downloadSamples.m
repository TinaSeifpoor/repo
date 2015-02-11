function [] = downloadSamples(textToImagePath, className)
%DOWNLOADSAMPLES Summary of this function goes here
%   Detailed explanation goes here
for i=1:numel(className)
    evalStr = ['!"' textToImagePath.bin '" "' className{i} '" "' textToImagePath.dir '" 20000'];
    eval(evalStr);
end
end

