% init
load('resume4');
addpath('../libsvm-3.20/matlab/');
%% Train SVM
samples = e.samples;
[classNames, ~, classes] = unique({samples(:).class});
[XTrain, XTest, yTrain, yTest]=separateData(e.layerX{1},classes,2000);
SVMG.model = libsvmtrain(XTrain,yTrain);
yPredict = libsvmpredict(SVMG.model, XTrain);
trainConfusion = calcConfusion(yPredict,yTrain)

yPredict = libsvmpredict(SVMG.model, XTest);
testConfusion = calcConfusion(yPredict, yTest)
save('result', 'trainConfusion', 'testConfusion', 'classNames')
% for idxClass=1:numel(classNames)
%     className = classNames(idxClass);
%     idxClassSamples = yTrain==idxClass;
%     XPositive = XTrain(idxClassSamples,:);
%     yPositive = ones(size(XPositive,1),1);
%     XNegative = XTrain(~idxClassSamples,:);
%     yNegative = zeros(size(XNegative,1),1);
%     SVM(idxClass).model = libsvmtrain([XNegative;XPositive], [yNegative;yPositive]);
%     %test
%     yPredict = libsvmpredict(SVM(idxClass).model,XPositive);
%     TP = mean(yPositive==yPredict)
%     yPredict = libsvmpredict(SVM(idxClass).model,XNegative);
%     TN = mean(yNegative==yPredict)
% end
% %% Test SVM
% load('db.mat');
% classNames = {Class(:).className};
% for i=1:numel(classNames)
%     [idxPicked, prob] = libsvmpredict(SVM(i).model,DB.Net.X, 5);
%     filesPicked = DB.Categorizer.imageFile(idxPicked);
%     for j=1:numel(filesPicked)
%         filePicked = filesPicked{j};
%         imcur = imread(filePicked);
%         %         figure;imshow(imcur);title(classNames{i});
%         outputfilename = strcat(classNames{i},num2str(j),'.jpg');
%         imwrite(imcur,outputfilename{:});
%     end
% end