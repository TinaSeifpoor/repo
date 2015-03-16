clear; close all; clc;
run('../matconvnet-1.0-beta7/matlab/vl_setupnn.m')
adjectives = {'lots of', 'dozens of', 'a few', 'single'};
bases = {'cars', 'flowers', 'children', 'books', 'phones', 'planes', 'monitors', 'laptops', 'mouse', 'buildings'};
net = 'imagenet-vgg-f.mat';
layers = [3,7,12,14,16,19];
%% Configuration
fakeExtract  = false;
fakeDownload = true;
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
    e.addLayers(layers(7));
    e.extract;
    save('resume', 'e', '-v7.3');
end
clear fakeExtract fakeDownload adjectives bases net layers source ans;