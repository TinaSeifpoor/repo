function [ trainSet, testSet ] = SortDataset( classList, featureList, trainPerc )
%SORTDATASET Rearranges feature & class lists into training & test sets
%   Takes feature vector (each row represents an instance) and
%   class list (each row represents an instance). Rearranges first trainPerc percent
%   of data to trainSet cell and rest to testSet where first element of the cell is class name, second element
%   is feature list.
uniqueClassList = unique(classList);
trainSet=cell(length(uniqueClassList),2);
testSet=cell(length(uniqueClassList),2);
for i=1:length(uniqueClassList)
    classIdx = find(strcmp(classList, uniqueClassList{i}));
    classTrainIdx = classIdx(1:uint8(length(classIdx)*trainPerc));
    classTestIdx = classIdx(uint8(length(classIdx)*trainPerc)+1:length(classIdx));
    trainSet(i,:)={uniqueClassList(i),featureList(classTrainIdx,:)};
    testSet(i,:)={uniqueClassList(i),featureList(classTestIdx,:)};
end
end

