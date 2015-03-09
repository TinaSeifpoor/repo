clear;clc;close all;
%% Re-get features?
getFeatures=true;
load('leaf-all');
if (getFeatures)
    %% Get dataset
    datasetPath = '../../../Dataset/swe/';
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
            %             ccddh = calcCCDDH(regLeaf,20);
            %             ncch = calcNCCH(regLeaf);
            tR = inertiaRotation(regLeaf);
%             regLeaf = pickHighestAreaRegion(imtransform(regLeaf, tR));
            regLeaf = pickHighestAreaRegion(imrotate(regLeaf, tR));
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
%% Decide nHarmonics
% nHarmonicsList = 40:50:990;
nHarmonicsList = 500:30:650;
perfTest=zeros(numel(nHarmonicsList),1);
for idxHar = 1:numel(nHarmonicsList)
    nHarmonics = nHarmonicsList(idxHar);
    measCurr = [fftXMList(:,1:nHarmonics),fftYMList(:,1:nHarmonics)];
    fprintf('nHarmonics: %d\n',nHarmonics);
    indices = crossvalind('Kfold',species,5);
    perfTesting = zeros(1,5);
    perfTraining = zeros(1,5);
    for i= 1:5
        test = (indices==i); train= ~test;
        measTest = measCurr(test,:); measTrain = measCurr(train,:); speciesTrain = species(train,:); speciesTest = species(test,:);
        [perfTesting(:,i), perfTraining(:,i)] =  classifySVM (measTrain, measTest, speciesTrain, speciesTest);
    end
    perfTest(idxHar,:) = mean(perfTesting,2);
end
smoothedPerfTest = smooth(perfTest,3);
[~, idxMax] = max(smoothedPerfTest);

h = figure;hold on;
plot(1:numel(perfTest),perfTest)
legend('Testing');
ylabel('Performance')
xlabel('Complexity (# of Harmonics)')
xlim([min(nHarmonicsList) max(nHarmonicsList)])
ylim([0 1])
% saveas(gcf, [keyword '-ComplexitySmooth'], 'jpg'); close(h);

h = figure;plot(idxList,perfTest)
hold on;
plot(idxList,perfTrain,'--r');
legend('Testing', 'Training');
ylabel('Performance')
xlabel('Complexity (# of Harmonics)')
xlim([0 15])
ylim([0 1])
% saveas(gcf, [keyword '-Complexity' num2str(performanceTest*100,2)], 'jpg');close(h);
%% all
perfTest=zeros(16,1);
perfTrain=zeros(16,1);
nHarmonicsList=620;
    keyword = ['xy-anglesMeasAll-' num2str(nHarmonicsList) 'H'];
    measCurr = [meas,atan(fftXMList(:,1:nHarmonicsList)),atan(fftYMList(:,1:nHarmonicsList))];
    indices = crossvalind('Kfold',species,5);
    similarityMatrixTraining = zeros(numel(unique(species))); similarityMatrixTesting = zeros(numel(unique(species)));
    perfTesting = zeros(numel(unique(species)),5);
    perfTraining = zeros(numel(unique(species)),5);
    for i= 1:5
        test = (indices==i); train= ~test;
        measTest = measCurr(test,:); measTrain = measCurr(train,:); speciesTrain = species(train,:); speciesTest = species(test,:);
        [similarityMatrixTesting1, similarityMatrixTraining1, ~, ~] =  classifySVM (measTrain, measTest, speciesTrain, speciesTest);
        perfTesting(:,i)=diag(similarityMatrixTesting1);
        perfTraining(:,i)=diag(similarityMatrixTraining1);
        similarityMatrixTesting = similarityMatrixTesting1 + similarityMatrixTesting; similarityMatrixTraining = similarityMatrixTraining1 + similarityMatrixTraining;
    end
    PlotPerformance(mean(perfTraining,1),[keyword '-initTrainingPerf']);
    PlotPerformance(mean(perfTesting,1),[keyword '-initTestingPerf']);
    similarityMatrixTesting = similarityMatrixTesting/5; similarityMatrixTraining = similarityMatrixTraining/5;
    perfTesting = diag(similarityMatrixTesting);perfTraining = diag(similarityMatrixTraining);
    perfMeanTesting = mean(perfTesting); perfSTDTesting = std(perfTesting); perfMeanTraining = mean(perfTraining); perfSTDTraining = std(perfTraining);
    figure;imagesc(similarityMatrixTesting);
    saveas(gcf, [keyword '-confusionTestingMatrix'], 'jpg');
    figure;imagesc(similarityMatrixTraining);
    saveas(gcf, [keyword '-confusionTrainingMatrix'], 'jpg');
    close all;
    perfTest(nHarmonicsList+1) = mean(perfTesting);
    perfTrain(nHarmonicsList+1) = mean(perfTraining);
smoothedPerfTest = smooth(perfTest,3);
[~, idxMax] = max(perfTest);
performanceTest = perfTest(idxMax);
performanceTrain = perfTrain(idxMax);
keyword = ['xy-' num2str(idxMax-1) 'H'];
idxList = 0:15;

h = figure;hold on;
plot(idxList,smoothedPerfTest)
plot(idxList,perfTrain,'--r')
legend('Testing', 'Training');
ylabel('Performance')
xlabel('Complexity (# of Harmonics)')
xlim([0 15])
ylim([0 1])
saveas(gcf, [keyword '-ComplexitySmooth'], 'jpg'); close(h);

h = figure;plot(idxList,perfTest)
hold on;
plot(idxList,perfTrain,'--r');
legend('Testing', 'Training');
ylabel('Performance')
xlabel('Complexity (# of Harmonics)')
xlim([0 15])
ylim([0 1])
saveas(gcf, [keyword '-Complexity' num2str(performanceTest*100,2)], 'jpg');close(h);