clear;clc;close all;
%% Re-get features?
getFeatures=true;
% load('leaf-all');
if (getFeatures)
    %% Get dataset
    datasetPath = '../../../Dataset/flavia/';
    dataset = parseDataset(datasetPath);
    %% Get n files per class
    %     dataset= modifyDataset(dataset,10);
    %% Get images
    measCurr = [];
    fftXAList = [];
    fftXMList = [];
    fftYAList = [];
    fftYMList = [];
    species = [];
    for idxClass=1:numel(dataset)
        class = dataset{idxClass};
        for idxInstance = 1:numel(class)
            filename = class{idxInstance};
            filename = filename(1:numel(filename)-4);
            imInstance = imread(class{idxInstance});
            regLeaf = segmentLeaf(imInstance);
%             tR = inertiaRotation(regLeaf);
%             regLeaf = pickHighestAreaRegion(imrotate(regLeaf, tR));
            getFeatureVector(regLeaf, im);
%             figure;imshow(regLeaf)
%            filenameBW = [filename '-inertiaBW.jpg'];
%            imwrite(regLeaf, filenameBW);
             [fftXA, fftXM, fftYA, fftYM, imFD] = calcFD(regLeaf, 1000);
%            filenameFD = [filename '-fd32.jpg'];
%            imwrite(imFD, filenameFD);
            fftXAList = [fftXAList;fftXA];
            fftXMList = [fftXMList;fftXM];
            fftYAList = [fftYAList;fftYA];
            fftYMList = [fftYMList;fftYM];
            species = [species;idxClass]; %#ok<AGROW>
        end
    end
    save('leaf-all', 'fftXAList', 'fftXMList', 'fftYAList', 'fftYMList', 'meas', 'species');
end