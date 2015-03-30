function result = performValidation(X,y,trainRatio)
%PERFORMVALÝDATÝON Summary of this function goes here
%   Detailed explanation goes here
[XTrain, XTest, yTrain, yTest]=separateData(X,y,trainRatio);

result.model = libsvmtrain(XTrain,yTrain);
result.train = performPrediction(result.model, XTrain, yTrain);
result.valid = performPrediction(result.model, XTest, yTest);
end

function t = performPrediction(model, X, y)
t.yPredict = libsvmpredict(model, X);
t.confusion = calcConfusion(t.yPredict,y);
sum(diag(t.confusion))/numel(y)
end

