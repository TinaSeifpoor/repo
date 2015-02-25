init


% %% Train SVM
% for i=1:numel(Class)
%     X = {Class(:).X};
%     X(i)=[];
%     XNegative = cell2mat(X');
%     yNegative = -ones(size(XNegative,1),1);
%     XPositive = Class(i).X;
%     yPositive = ones(size(XPositive,1),1);
%     SVM(i).model = libsvmtrain([XNegative;XPositive], [yNegative;yPositive]);
%     %     X = [XNegative;XPositive];
%     %     y = [yNegative;yPositive];
%     %     save('svm_sample.mat','X','y');
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