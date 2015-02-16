function [ trainFeatures, trainClasses, testFeatures, testClasses,...
    uniqueClassList ] = SortDataset( classList, featureList, trainPerc )
%SORTDATASET Rearranges feature & class lists into training & test sets
%   Takes feature vector (each row represents an instance) and
%   class list (each row represents an instance). Rearranges first trainPerc percent
%   of data to trainSet cell and rest to testSet where first element of the cell is class name, second element
%   is feature list.
uniqueClassList = unique(classList);
trainFeatures=[];
trainClasses=[];
testFeatures=[];
testClasses=[];
for i=1:length(uniqueClassList)
    classIdx = find(strcmp(classList, uniqueClassList{i}));
    classTrainIdx = classIdx(1:uint8(length(classIdx)*trainPerc));
    classTestIdx = classIdx(uint8(length(classIdx)*trainPerc)+1:length(classIdx));
    trainFeatures = [trainFeatures;featureList(classTrainIdx,:)];
    trainClasses = [trainClasses;repmat(i,numel(classTrainIdx),1)];
    testFeatures = [testFeatures;featureList(classTestIdx,:)];
    testClasses = [testClasses;repmat(i,numel(classTestIdx),1)];
end
end

