clear; close all; clc;
run('../matconvnet-1.0-beta7/matlab/vl_setupnn.m')
% adjectives = {'lots of', 'dozens of', 'a few', 'single'};
adjectives = {...
    '15th century painting portraits of', ...
    '16th century painting portraits of', ...
    '17th century painting portraits of', ...
    '18th century painting portraits of', ...
    '19th century painting portraits of', ...
    '20th century painting portraits of'};
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