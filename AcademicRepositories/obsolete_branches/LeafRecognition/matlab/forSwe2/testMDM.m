clear;clc;close all;

getFeatures=false;
% load('leaf-all');
load('idxTest');
if (getFeatures)
    %% Get dataset
    datasetPath = '../../Dataset/swe/';
    dataset = parseDataset(datasetPath);
    %% Get n files per class
    %     dataset= modifyDataset(dataset,10);
    %% Get images
    measCurr = [];
    featBMDMList = [];
    featMMDMList = [];
    featAMDMList = [];
    species = [];
    for idxClass=1:numel(dataset)
        class = dataset{idxClass};
        for idxInstance = 1:numel(class)
            filename = class{idxInstance};
            filename = filename(1:numel(filename)-4);
            filenameBW = [filename '-inertiaBW.jpg'];
            if (exist(filenameBW,'file'))
                regLeaf = imread(filenameBW);
            else
                imInstance = imread(class{idxInstance});
                regLeaf = segmentLeaf(imInstance);
                %             ccddh = calcCCDDH(regLeaf,20);
                %             ncch = calcNCCH(regLeaf);
                tR = inertiaRotation(regLeaf);
                %             regLeaf = pickHighestAreaRegion(imtransform(regLeaf, tR));
                regLeaf = pickHighestAreaRegion(imrotate(regLeaf, tR));
                %             figure;imshow(regLeaf)
                filenameBW = [filename '-inertiaBW.jpg'];
                imwrite(regLeaf, filenameBW);
            end
            [featBMDM,featAMDM,featMMDM]= calcMDM(regLeaf>0,50);
            featBMDMList = [featBMDMList,featBMDM(:)]; %#ok<AGROW>
            featAMDMList = [featAMDMList,featAMDM(:)]; %#ok<AGROW>
            featMMDMList = [featMMDMList,featMMDM(:)]; %#ok<AGROW>
            species = [species;idxClass]; %#ok<AGROW>
        end
    end
    save('leaf-mdm', 'featBMDMList', 'featAMDMList', 'featMMDMList', 'species');
else
    load('leaf-mdm');
end
%% Determine k
% kList = 1:10;
% optimizeMDM(kList, species, idxTest, featBMDMList,...
%     featAMDMList, featMMDMList);
%% Determine weights
k=5;
[featListTrain, speciesTrain, ~, ~]...
    = SplitDataset(idxTest, species, featAMDMList);
%
perfK = optimizeKNN(speciesTrain, featListTrain, k);
mdmWeights = squeeze(mean(perfK,2));
plot(mdmWeights,'--rs');
xlabel('Species');ylabel('Weights (5-fold crossvalidation performance)')
xlim([1 32]);
save('leaf-mdmForCascade', 'species', 'idxTest', 'featAMDMList', 'mdmWeights', 'k');
% k = 6;
% [featListTrain, speciesTrain, featListTest, speciesTest]...
%     = SplitDataset(idxTest, species, featAMDMList);
% speciesTestPre = knnclassify(featListTest', featListTrain', speciesTrain', 5);
% [confusionMatA, perfListA] = genConfusionMatrix(speciesTest, speciesTestPre);
% figure;imagesc(confusionMatA);
% %
% %%