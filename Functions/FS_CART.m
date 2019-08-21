function acc = FS_CART(train, test, rank)

    num_F = size(train, 2) - 1;
    Vectors = 1:num_F;
    Target = num_F + 1;
    num_test = size(test, 1);
    
    train_X = train(:, Vectors);
    train_y = train(:, Target);
    test_X = test(:, Vectors);
    test_y = test(:, Target);
    
    Mdl = fitctree(train_X, train_y);
    test_pred = predict(Mdl, test_X);
    
    acc_test = sum(test_pred == test_y)/num_test;
    
    acc = [acc_test];
    rank = fliplr(rank);
    
    for removeN = 1:num_F-1
        vector = Vectors;
        vector(rank(1:removeN)) = [];
        
        train_M = train_X(:, vector);
        test_M = test_X(:, vector);
        
        Mdl = fitctree(train_M, train_y);
        test_pred = predict(Mdl, test_M);
        
        acc_test_N = sum(test_pred == test_y)/num_test;
        acc = [acc; acc_test_N];
end