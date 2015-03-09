function [featListTrain, speciesTrain, featListTest, speciesTest]...
    = SplitDataset(idxTest, species, featList)
%SPLITDATASET Summary of this function goes here
%   Detailed explanation goes here
featListTest = featList(:,idxTest);
speciesTest = species(idxTest);
featListTrain = featList(:,~idxTest);
speciesTrain = species(~idxTest);
end

