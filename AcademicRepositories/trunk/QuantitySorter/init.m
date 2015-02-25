clear; close all; clc;
run('../matconvnet-1.0-beta7/matlab/vl_setupnn.m')

%% Configuration
fakeExtract  = false;
%%
if (fakeExtract)
    load('resume');
else
    %% Downloader
    fakeDownload = true;
    dl = DownloaderAdjective;
    dl.addAdjective('lots of')
    dl.addAdjective('dozens of')
    dl.addAdjective('a few')
    dl.addAdjective('single')
    dl.addBase('cars')
    dl.addBase('flowers')
    dl.addBase('children')
    dl.addBase('books')
    dl.addBase('phones')
    dl.addBase('planes')
    dl.addBase('monitors')
    dl.addBase('laptops')
    dl.addBase('mouse')
    dl.addBase('buildings')
    %% Extractor
    e = Extractor(load('imagenet-vgg-f.mat'));
    e.setSource(dl.download(fakeDownload));
    e.addLayer(19);
    e.extract;
    save('resume', 'e');
end