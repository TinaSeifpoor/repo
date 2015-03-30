classdef Extractor < handle
    %EXTRACTOR Summary of this class goes here
    %   Detailed explanation goes here
    
    properties(SetAccess = protected, GetAccess = public)
        net;
        layers;
        source;
        layerX;
        samples;
    end
    
    methods
        function e = Extractor(net)
            e.net = net;
        end
        function addLayer(e,layer)
            e.layers(length(e.layers)+1) = layer;
        end
        function addLayers(e,layers)
            e.layers(length(e.layers)+1:length(e.layers)+length(layers)) = layers;
        end
        function setSource(e,source)
            e.source = source;
        end
        function extract(e)
            successList = true(numel(e.source),1);
            e.layerX = cell(length(e.layers),1);
            for idxSample = 1:numel(e.source)
                try
                    sampleOut = extractFromSample(e.source(idxSample),e.net,e.layers);
                    for idxLayer=1:length(e.layers)
                        sampleOutLayer = sampleOut{idxLayer};
                        sampleOutLayer = reshape(sampleOutLayer,[1,size(sampleOutLayer)]);
                        e.layerX{idxLayer} = [e.layerX{idxLayer};sampleOutLayer];
                    end
                    fprintf('%s extracted.\n', e.source(idxSample).path);
                catch
                    successList(idxSample)=false;
                end
            end
            e.samples = e.source(successList);
        end
    end
    
end

function sampleOut = extractFromSample(sample, net, layers)
filePath = sample.path;
im = imread(filePath) ;
im_ = imresize(im, net.normalization.imageSize(1:2)) ;
im_ = single(im_ - uint8(net.normalization.averageImage));
% run the CNN
res = vl_simplenn(net, im_);
sampleOut = {res(layers).x};
end
