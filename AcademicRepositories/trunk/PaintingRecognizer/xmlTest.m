close all; clear; clc;

xmlBasePath = 'D:\downloads\rijksjpg\xml2\';
xmlList = getFileList(xmlBasePath);

id = randperm(xmlList,1:10);
xmlList = xmlList(id);