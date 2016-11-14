% Symmetric Rank-K update (SYRK): COL MAJOR
% The SYRK operation computes C := C + AAT with a rectangular matrix A ? Rn×m, 
% updating only the lower triangular part of the symmetric matrix C ? Rn×n. 
% Matrix transposition needs to be implemented to perform this operation efficiently. 

function C = COL_SYRK_BLOCK(C, A, m, n) %C -> Rmxm, A-> Rmxk, block -> Rnxn
    u = 1;
    for j = 1:n:m
        for i = u:n:m
            C(i:i+n-1,j:j+n-1) = SYRK_UNBLOCK(C(i:i+n-1,j:j+n-1), A(i:i+n-1,1:end), A(j:j+n-1,1:end)');
            C(j:j+n-1,i:i+n-1) = C(i:i+n-1,j:j+n-1)';
        end
        u = u+n;
    end
end
