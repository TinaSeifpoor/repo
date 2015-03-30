downloadertest;
run('../matconvnet-1.0-beta7/matlab/vl_setupnn.m');
e = Extractor(load('imagenet-vgg-f.mat'));
e.setSource(a);
e.addLayer(3);
e.addLayer(8);
e.addLayer(19);
out = e.extract;