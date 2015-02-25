classdef Extractor < handle
    %EXTRACTOR Summary of this class goes here
    %   Detailed explanation goes here
    
    properties(SetAccess = protected, GetAccess = public)
        net;
        layers;
        source;
        extractOut;
    end
    
    methods
        function e = Extractor(net)
            e.net = net;
        end
        function addLayer(e,layer)
            e.layers(length(e.layers)+1) = layer;
        end
        function setSource(e,source)
            e.source = source;
        end
        function extractOut = extract(e)
            successList = true(numel(e.source),1);
            outputCell = cell(0);
            for idxSample = 1:numel(e.source)
                try
                    sampleOut = extractFromSample(e.source(idxSample),e.net,e.layers);
                    outputCell(size(outputCell,1)+1,:)=sampleOut;
                    fprintf('%s extracted.\n', e.source(idxSample).path);
                catch
                    successList(idxSample)=false;
                end
            end
            samples = e.source(successList);

            e.extractOut = cell(0);
            for idxLayer = 1:numel(e.layers)
                samplesLayer = samples;
                layerX = outputCell(:,idxLayer);
                [samplesLayer(:).X] = layerX{:};
                e.extractOut{idxLayer} = samplesLayer;
            end
            extractOut = e.extractOut;
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
