function [confusionMat, perfList] = genConfusionMatrix(speciesTest, speciesTestPre)
%GENCONFUSIONMATRIX Summary of this function goes here
%   Detailed explanation goes here
speciesU = unique(speciesTest);
nSpeciesU = numel(speciesU);
%%
confusionMat = zeros(nSpeciesU);
for idxSpecies1=1:nSpeciesU
    speciesS1 = speciesU(idxSpecies1);
    idxSpeciesTest1 = (speciesTest==speciesS1);
    speciesTestPre1 = speciesTestPre(idxSpeciesTest1);
    for idxSpecies2 = 1:nSpeciesU
        speciesS2 = speciesU(idxSpecies2);
        confusionMat(idxSpecies1,idxSpecies2) = numel(find(speciesTestPre1==speciesS2));
    end
end
confusionMat = bsxfun(@rdivide, confusionMat, sum(confusionMat,2));
%%
perfList = diag(confusionMat);
end

