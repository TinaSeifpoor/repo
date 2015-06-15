clear;close all;

load('db');

% Terrible hack! Please forgive me%
iremove = cell2mat({strcmp({db(:).era},'1559')});
db(iremove) = [];
%%

imale = cell2mat({strcmp({db(:).gender},'men')});
dbMale = db(imale);
dbFemale = db(~imale);

[meanColorMale,eraMale]=analyzeClothData(dbMale);
[meanColorFemale,eraFemale]=analyzeClothData(dbFemale);


meanColorMid = uint8(zeros(size(meanColorMale)));
meanColorEras = cat(1,meanColorMale,meanColorMid,meanColorFemale);

imshow(meanColorEras)
