clear; close all; clc;
run('../matconvnet-1.0-beta7/matlab/vl_setupnn.m')
% adjectives = {'lots of', 'dozens of', 'a few', 'single'};
adjectivesPre = cellfun(@num2str, num2cell(1901:3:2015), 'UniformOutput', false);
adjectivesMid = {' painting portraits of '};
adjectives = strcat(adjectivesPre, repmat(adjectivesMid,1,size(adjectivesPre,2)));
bases = {'men', 'women'};
net = 'imagenet-vgg-f.mat';
layers = [19];
%% Configuration
fakeExtract  = false;
fakeDownload = false;
%%
if (fakeExtract)
    load('resume');
else
    %% Downloader
    dl = DownloaderAdjective;
    dl.addAdjectives(adjectives);
    dl.addBases(bases);
    source = dl.download(fakeDownload);
    %% Extractor
    e = Extractor(load(net));
    e.setSource(source);
    e.addLayers(layers(1));
    e.extract;
    save('resume', 'e', '-v7.3');
end
clear fakeExtract fakeDownload adjectives bases net layers source ans;