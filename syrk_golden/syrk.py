import os
import sys
import numpy as np
import random


''' Naive Matrix-Matrix Multiplication, usiing 3 For loops
	Provides golden model output for other implementations
'''
def simpleGEMM(A, nRows):
	prod = np.zeros((nRows, nRows))
	transA = A.T
	for i in range(nRows):
		for j in range(nRows):
			for k in range(nRows):
				prod[i,j] += A[i,k]*transA[k,j]

	return prod


''' Unblocked version of Symmetric Rank-K update. Uses a
series of Rank-1 updates to find the matrix product of 
A and A.T, which are blocked matrices.
'''
def unblocked_syrk(blkA, blkB, nrows, blkSize):
	prod = np.zeros((blkSize, blkSize))
	for i in range(nrows):
		prod += np.outer(blkA[:,i],blkB[i,:])

	return prod


''' Blocked version of Symmetric Rank-K update. Divides
A by rows and A.T by columns, and then uses the Unblocked
version of Symmetric rank-K update to compute the matrix
product 
'''
def blocked_syrk(blkA, nrows, blkSize):
	prod = np.zeros((nrows,nrows))
	blkATrans = blkA.T
	for i in range(nrows/blkSize):
		for j in range(i+1):
			lr = i*blkSize
			ur =  (i+1)*blkSize 
			lc = j*blkSize
			uc = (j+1)*blkSize 
			prod[lr:ur,lc:uc] = unblocked_syrk(blkA[lr:ur,:],blkATrans[:,lc:uc], nrows, blkSize)
			prod[lc:uc,lr:ur] = prod[lr:ur,lc:uc].T

	return prod


def main():
	nRows = int(sys.argv[2])
	blkSize = int(sys.argv[3])
	lapu_size = int(sys.argv[1])
	if nRows%lapu_size != 0:
		print("The number of rows of matrix {} is not a multiple of LAPU size {}".format(nRows, lapu_size))
		print("Exiting........")
		exit(1)

	if blkSize%lapu_size != 0:
		print("The block size {} being used for partitioning is not a multiple of LAPU size {}".format(blkSize, lapu_size))
		print("Exiting........")
		exit(1)

	if nRows%blkSize != 0:
		print("The matrix cannot be partioned into equal blocks")
		print("Exiting........")
		exit(1)

	A = np.random.randint(100, size=(nRows, nRows))
	print("Matrix being used for Symmetrix Rank-K update test is {}".format(A))
	gemmResult = simpleGEMM(A, nRows)
	unblkRes = unblocked_syrk(A,A.T, nRows, nRows)
	blkRes = blocked_syrk(A,nRows,blkSize)

	print("The product of A and A.T is {}".format(gemmResult))
	print("The difference between the unblocked and naive implementation is {}".format(np.sum((unblkRes - gemmResult)**2)))
	print("The difference between the blocked and unblocked implementation is {}".format(np.sum((blkRes - unblkRes)**2)))



if __name__ == '__main__':
	main()

