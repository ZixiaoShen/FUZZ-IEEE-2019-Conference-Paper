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

%% Feature Selection Process
% IFS
[r_IFS, w_IFS] = infFS(train_X, train_y, 0.5, 1, 0);

% ILFS
[r_ILFS, w_ILFS] = ILFS(train_X, train_y, 6, 0);

% ReliefF
[r_ReliefF, w_ReliefF] = reliefF(train_X, train_y, 20);

% MIFS
[r_MIFS, w_MIFS] = mutInfFS(train_X, train_y, num_F);


%% 
w_IFS_norm = mapminmax(w_IFS, 0, 1);
