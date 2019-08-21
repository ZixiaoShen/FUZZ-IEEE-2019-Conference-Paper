clear;
clc;

%% load the data
load('/home/zealshen/Dropbox/DATA/UCI/WBC/wbc.mat');
data = table2array(breastcancerwisconsin);

%% data preprocessing
NaN_Column = find(any(isnan(data)));
NaN_Row = find(isnan(data(:, NaN_Column)));
data(NaN_Row, :) = [];
data = data(:, 2:11);
clear NaN_Column NaN_Row

%% set up X and y
num_F = size(data, 2) - 1;
Vectors = 1:num_F;
Target = num_F + 1;

X = data(:, Vectors);
y = data(:, Target);
y = y -3;
data = [X y];
%% divide the training and testing sets
proportion = 0.67;
[train, test] = split2train_test(data, proportion);

train_X = train(:, Vectors);
train_y = train(:, Target);

test_X = test(:, Vectors);
test_y = test(:, Target);

%% Classification Process
Mdl = fitctree(train_X, train_y);
train_pred = predict(Mdl, train_X);
test_pred = predict(Mdl, test_X);

num_train = size(train_X, 1);
num_test = size(test_X, 1);

acc_train = sum(train_pred == train_y)/num_train;
acc_test = sum(test_pred == test_y)/num_test;

%% Feature Selection Process
% IFS
[r_IFS, w_IFS] = infFS(train_X, train_y, 0.5, 1, 0);

%% IFS + Classification Process
acc_IFS = FS_CART(train, test, r_IFS);

RemoveN = 0:num_F-1;
h_IFS = plot(RemoveN, acc_IFS, 'LineWidth', 2);
xlabel('The number of the removed features');
ylabel('Classification Accuracy');
title('Comparison using CART in WBC');

