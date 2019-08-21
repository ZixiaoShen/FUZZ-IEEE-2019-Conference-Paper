<<<<<<< HEAD
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
=======
clear;
clc;

%% load the data
load('/home/zealshen/DATA/UCI_DATA/Parkinsons/Parkinsons.mat');

X = [parkinsons(:,2:17) parkinsons(:,19:24)];
y = parkinsons(:,18);

X = table2array(X);
y = table2array(y);

y = 2 * y - 1;
%% format the dataset
data = [X y];

Vectors = 1:22;
Target = 23;
%% divide the training and testing data
proportion = 0.67
[train_data, test_data] = split2train_test(data, proportion);

train_X = train_data(:, Vectors);
train_y = train_data(:, Target);
test_X = test_data(:, Vectors);
test_y = test_data(:, Target);


%% IFS
[r_IFS, w_IFS] = infFS(train_X, train_y, 0.5, 1, 0);

%% ILFS
[r_ILFS, w_ILFS] = ILFS(train_X, train_y, 6, 0);




>>>>>>> a87ab7d1e9bd8dd37bc363a32ced5fba5acea21c
