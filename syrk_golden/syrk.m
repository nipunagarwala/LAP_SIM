function out = syrk()
	A = rand(128,128);
	C_check = A*A';	%test, unblocked
	C_syrk_col = blocked_syrk_col(A);	%blocked
	if (sum(sum(tril(C_check) - tril(C_syrk_col))) < e^-10)
		fprintf("Column:  Correct\n")
	end
	C_syrk_row = blocked_syrk_row(A);
	if (sum(sum(tril(C_check) - tril(C_syrk_row))) < e^-10)
		fprintf("Row:  Correct\n")
	end
end

function C_4x4 = unblocked_syrk(A)
%unblocked SYRK
%compute 4x4 block of C using 4xkc block of A - just a GEMM with A and A'
kc = size(A,2);
C_4x4 = zeros(4,4);

for (i = 1:kc)
	Ai = A(:,i);
	Ai_t = A(:,i)';
	C_4x4 += Ai*Ai_t;
end
end

function C_col = blocked_syrk_col(A)
%blocked SYRK
%compute mcxmc block of C from mcxkc block of A using unblocked syrk kernel
mc = size(A,1);
kc = size(A,2);
C_col = zeros(mc,mc);

num_blocks = mc/4;

for (i = 1:num_blocks)
	A_block = A((i-1)*4+1:i*4,:);
	A_update = A(i*4+1:end,:);
	%Calculate the diagonal block using unblocked syrk
	C_col((i-1)*4+1:i*4, (i-1)*4+1:i*4) = unblocked_syrk(A_block);
	%update column block underneath
	C_col(i*4+1:end, (i-1)*4+1:i*4) += A_update*A_block';
end
end


function C_row = blocked_syrk_row(A)
mc = size(A,1);
kc = size(A,2);
C_row = zeros(mc,mc);
num_blocks = mc/4;
for (i = 1:num_blocks)
	A_block = A((i-1)*4+1:i*4,:);
	A_update = A(1:(i-1)*4,:);
	C_row((i-1)*4+1:i*4,(i-1)*4+1:i*4) = unblocked_syrk(A_block);
	C_row((i-1)*4+1:i*4,1:(i-1)*4) += A_block*A_update';
end
end

%{
function C_row = blocked_syrk_row(A)
mc = size(A,1);
kc = size(A,2);
C_row = zeros(mc,mc);
num_blocks = mc/4;
for (i = 1:num_blocks)
	A_block = A(mc-i*4+1:mc-(i-1)*4,:);
	A_update = A(1:mc-i*4,:);
	C_row(mc-i*4+1:mc-(i-1)*4,mc-i*4+1:mc-(i-1)*4) = unblocked_syrk(A_block);
	C_row(mc-i*4+1:mc-(i-1)*4,1:mc-i*4) += A_block*A_update';
end
end
%}
