m = 4*5;
n = 4;
k = n*6;
C = zeros(m,m);
A = randi(10,m,k);

X = A*A';
Y = SYRK_UNBLOCK(C, A, A');
test_unblocked = X\Y %<-- if this equals the Identity matrix then SYRK_UNBLOCK works

Y = COL_SYRK_BLOCK(C, A, m, n);
test_col_major = X\Y %<-- if this equals the Identity matrix then COL_SYRK_UNBLOCK works

Y = ROW_SYRK_BLOCK(C, A, m, n);
test_row_major = X\Y %<-- if this equals the Identity matrix then ROW_SYRK_UNBLOCK works

Y = DIAG_SYRK_BLOCK(C, A, m, n)
test_diag_major = X\Y %<-- if this equals the Identity matrix then DIAG_SYRK_UNBLOCK works



