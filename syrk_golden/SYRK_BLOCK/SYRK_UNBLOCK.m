% Symmetric Rank-K update (SYRK): 
% The SYRK operation computes C := C + AAT with a rectangular matrix A ? Rn×m, 
% updating only the lower triangular part of the symmetric matrix C ? Rn×n. 
% Matrix transposition needs to be implemented to perform this operation efficiently. 

function C = SYRK_UNBLOCK(C, A, Atran)
    
    for i = 1:size(A,2)
        C = C + A(:,i)*Atran(i,:);
    end

end