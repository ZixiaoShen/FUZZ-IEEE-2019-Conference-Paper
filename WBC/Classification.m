clear;
clc;

%% load the data
load('/home/zealshen/DATA/UCI_DATA/WBC/wbc.mat');

data = table2array(breastcancerwisconsin);

%% data preprocessing
NaN_Column = find(any(isnan(data)));
NaN_Row = find(isnan(data(:, NaN_Column)));
data(NaN_Row, :) = [];
data = data(:, 2:11);
clear NaN_Column NaN_Row

