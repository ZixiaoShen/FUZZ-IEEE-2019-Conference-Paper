clear;
clc;

%% load the data
load('D:/CloudFiles/OneDriveFiles/DATA/UCI_DATA/Parkinsons/parkinsons.mat');

X = [parkinsons(:, 2:17) parkinsons(:, 19:24)];
y = parkinsons(:, 18);

X = table2array(X);
y = table2array(y);

y = 2 * y - 1;

%% feature selection