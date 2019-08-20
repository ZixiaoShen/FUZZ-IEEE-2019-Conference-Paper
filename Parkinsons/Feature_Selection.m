clear;
clc;

%% 
load('/home/zealshen/DATA/UCI_DATA/Parkinsons/Parkinsons.mat');

X = [parkinsons(:,2:17) parkinsons(:,19:24)];
y = parkinsons(:,18);

X = table2array(X);
y = table2array(y);

y = 2 * y - 1;

%% IFS
[r, w] = infFS(X, y, 0.5, 1, 0);

