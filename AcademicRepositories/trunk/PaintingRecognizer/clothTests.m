clear; close all; clc;
detectors = {vision.CascadeObjectDetector,vision.CascadeObjectDetector('ProfileFace'),vision.CascadeObjectDetector('UpperBody')};
detecBias = {[0,1,30,30],[0,.8,30,30],[0,0.4,30,30]};
dataBasePath = './hitOutput/';
outpBasePath = './clothOutput/';
mkdir(outpBasePath);
eras = getDirList(dataBasePath);
db=struct;
basicCounter=1;
saveCounterLimit=20;
for idxEra=1:numel(eras)
    eraBasePath = [dataBasePath eras{idxEra} '/'];
    genders = getDirList(eraBasePath);
    for idxGen=1:numel(genders)
        fprintf('\nEra: %s\nGender: %s\n', eras{idxEra}, genders{idxGen});
        genderBasePath = [eraBasePath genders{idxGen} '/'];
        fList = getFileList(genderBasePath);
        for idxIm=1:numel(fList)
            imPath = [genderBasePath fList{idxIm}];
            try
                im = imread(imPath);
                totalMiss = true;
                cbox=[];
                for idxDet=1:numel(detectors)
                    bbox = step(detectors{idxDet},im);
                    bias=detecBias{idxDet};
                    ccbox(1) =  round(bbox(1)+bbox(3)/2);
                    ccbox(2) = round(bbox(2)+bbox(4)+bbox(4)*bias(2));
                    ccbox(3)=round(bias(3));
                    ccbox(4)=round(bias(4));
                    imCloth = im(ccbox(2):ccbox(2)+ccbox(4)-1,ccbox(1):ccbox(1)+ccbox(3)-1,1:3);
                    if (size(imCloth,1)==ccbox(3) && size(imCloth,2)==ccbox(4))
                        ibody = insertObjectAnnotation(im, 'rectangle',bbox,['Detect',num2str(idxDet)]);
                        ibody = insertObjectAnnotation(ibody, 'rectangle',ccbox,['Cloth',num2str(idxDet)]);
%                         outputFile = [outpBasePath genders{idxGen} '_' eras{idxEra} '_' num2str(idxIm) '-' num2str(idxDet)];
%                         outputFile = [outputFile, '.jpg']
                        db(basicCounter).inputFileName = imPath;
%                         db(basicCounter).outputFileName = outputFile;
                        db(basicCounter).imCloth = imCloth;
                        db(basicCounter).gender = genders{idxGen};
                        db(basicCounter).era = eras{idxEra};
                        basicCounter=basicCounter+1;
                        if (mod(basicCounter,saveCounterLimit)==0)
                            save('db', 'db');
                        end
%                         imwrite(ibody, outputFile);
                        break;
                    end
                end
            catch
            end
        end
    end
end