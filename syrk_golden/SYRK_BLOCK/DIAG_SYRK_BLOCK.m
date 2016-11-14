% Symmetric Rank-K update (SYRK): DIAGONAL MAJOR
% The SYRK operation computes C := C + AAT with a rectangular matrix A ? Rn×m, 
% updating only the lower triangular part of the symmetric matrix C ? Rn×n. 
% Matrix transposition needs to be implemented to perform this operation efficiently. 

function C = DIAG_SYRK_BLOCK(C, A, m, n) %C -> Rmxm, A-> Rmxk, block -> Rnxn    
    k = 1:n:m;
    l = 1:n:m;
    for i = 1:m/n
        for j = 1:length(k)
            C(k(j):k(j)+n-1,l(j):l(j)+n-1) = SYRK_UNBLOCK(C(k(j):k(j)+n-1,l(j):l(j)+n-1), A(k(j):k(j)+n-1,1:end), A(l(j):l(j)+n-1,1:end)');
            C(l(j):l(j)+n-1,k(j):k(j)+n-1) = C(k(j):k(j)+n-1,l(j):l(j)+n-1)';
        end
        k(1) = [];
        l(end) = [];
    end
end