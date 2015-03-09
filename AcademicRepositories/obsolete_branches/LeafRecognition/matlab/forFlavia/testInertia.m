clear;clc;close all;
datasetPath = '../Dataset/flavia/';
dataset = parseDataset(datasetPath);
idxClass = 5;
idxInstance = 5;
class = dataset{idxClass};
filename = class{idxInstance};
filename = filename(1:numel(filename)-4);
imInstance = imread(class{idxInstance});
reg = segmentLeaf(imInstance);
filename = 'LeafRotation';
for rot=0:45:360
    regC = imrotate(reg,rot);
    tR = inertiaRotation(regC);
    regCR = pickHighestAreaRegion(imrotate(regC, tR));
    filenameC = [filename num2str(rot) '.jpg'];
    imwrite(regC, filenameC, 'jpg');
    filenameR = [filename 'Inertia' num2str(rot) '.jpg'];
    imwrite(regCR, filenameR, 'jpg');
end


