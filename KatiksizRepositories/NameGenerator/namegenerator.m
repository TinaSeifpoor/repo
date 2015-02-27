clear;clc;close all;

names = readText('d:/names.txt');
[prob, letters] = genProb(names);
save('nameGenerator', 'prob','letters');
