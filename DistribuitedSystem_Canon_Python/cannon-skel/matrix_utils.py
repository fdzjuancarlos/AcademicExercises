# -*- mode:python; coding:utf-8; tab-width:4 -*-

import Ice
Ice.loadSlice('-I {} cannon.ice'.format(Ice.getSliceDir()))
import Cannon
import math

import itertools
from copy import copy, deepcopy


def matrix_multiply(A, B):
    order = A.ncols
    C = Cannon.Matrix(order, [])

    for i, j in itertools.product(xrange(order), repeat=2):
        C.data.append(
            sum(A.data[i * order + k] * B.data[k * order + j] for k in xrange(order))
        )

    return C
    
def printMatrix(A):
	order= A.ncols
	
	for i in range(0,order):
		for j in range(0, order):
			print A.data[i*order + j],
		print("")

		
def list_split(oldList, order):
	newList = list()
	auxList = list()
	for i in xrange(0, len(oldList)):
		auxList.append(oldList[i])
		if(len(auxList) == order):
			newList.append(auxList)
			auxList = list()
	return newList
			
def matrix_split(A, block_order):
	numMatrix = A.ncols/block_order
	allMatrix = [[[] for x in range(numMatrix)] for x in range(numMatrix)] 
	for i in xrange(0,numMatrix):
		for k in xrange(0, numMatrix):
			newMatrix = []
			for j in xrange(0,block_order):
				for m in xrange(0,block_order):
					newMatrix.append(getData(A,A.ncols,j+i*block_order,m+k*block_order))
			allMatrix[i][k]=newMatrix

	return normalMatrix_to_unidimensionalCannonMatrix(allMatrix, numMatrix ,block_order)
	
def matrix_split_data(A, block_order):
	numMatrix = A.ncols/block_order
	allMatrix = [[[] for x in range(numMatrix)] for x in range(numMatrix)] 
	for i in xrange(0,numMatrix):
		for k in xrange(0, numMatrix):
			newMatrix = []
			for j in xrange(0,block_order):
				for m in xrange(0,block_order):
					newMatrix.append(getData(A,A.ncols,j+i*block_order,m+k*block_order))
			allMatrix[i][k]=newMatrix
	
	return allMatrix
	
	
	
def matrix_horizontal_shift(A, block_order):
	numMatrix = A.ncols/block_order
	if(block_order == 1):
		allMatrix = copy_Matrix(A, block_order)
	else:
		allMatrix = matrix_split_data(A, block_order)
	for i in xrange(0,numMatrix):
		for j in xrange(0,i):
			temporal = deepcopy(allMatrix)
			for k in xrange(0,numMatrix):
				if k == 0:
					m=k
					allMatrix[i][numMatrix-1-m] = temporal[i][m]
				else:
					m=numMatrix-k
					allMatrix[i][numMatrix-1-k] = temporal[i][m]
	if not (block_order == 1):
		singleMatrix = quitThreeDimensions(allMatrix,block_order, A.ncols/block_order)
		return Cannon.Matrix(A.ncols, singleMatrix)
		

	return Cannon.Matrix(A.ncols, normalMatrix_to_unidimensionalMatrix(allMatrix, numMatrix, block_order))
	
					
def matrix_vertical_shift(A, block_order):
	numMatrix = A.ncols/block_order
	if(block_order == 1):
		allMatrix = copy_Matrix(A, block_order)
	else:
		allMatrix = matrix_split_data(A, block_order)
	for i in xrange(0,numMatrix):
		for j in xrange(0,i):
			temporal = deepcopy(allMatrix)
			for k in xrange(0,numMatrix):
				if k == 0:
					m=k
					allMatrix[numMatrix-1-m][i] = temporal[m][i]
				else:
					m=numMatrix-k
					allMatrix[numMatrix-1-k][i] = temporal[m][i]
					
	if not (block_order == 1):
		singleMatrix = quitThreeDimensions(allMatrix,block_order, A.ncols/block_order)
		return Cannon.Matrix(A.ncols, singleMatrix)
		

	return Cannon.Matrix(A.ncols, normalMatrix_to_unidimensionalMatrix(allMatrix, numMatrix, block_order))
	
def copy_Matrix(CannonMatrix, block_order):
	numMatrix = CannonMatrix.ncols/block_order
	BallMatrix = []
	for i in xrange(0, numMatrix):
		BallMatrix.append([])
		for j in xrange(0, numMatrix):
			BallMatrix[i].append(getData(CannonMatrix, CannonMatrix.ncols, i, j))
	
	return BallMatrix
	
def quitThreeDimensions(A, block_order, numMatrix):
	doubleMatrix=list()
	for i in A:
		for j in i:
			doubleMatrix.append(j)
	
	singleMatrix=list()
	for z in xrange(0, numMatrix):
		for x in xrange(0, block_order):
			for i in xrange(0,numMatrix):
				for j in xrange(0,block_order):
						singleMatrix.append(doubleMatrix[i+z*numMatrix][j+x*block_order])
	return singleMatrix	
	
def normalMatrix_to_unidimensionalCannonMatrix(Matrix, length, blockOrder):
	unidimensionalMatrix= list()
	for i in xrange(length):
		for j in xrange(length):
			unidimensionalMatrix.append(Cannon.Matrix(blockOrder,Matrix[i][j]))
	return unidimensionalMatrix
	
def normalMatrix_to_unidimensionalMatrix(Matrix, length, blockOrder):
	unidimensionalMatrix= list()
	for i in xrange(length):
		for j in xrange(length):
			unidimensionalMatrix.append(Matrix[i][j])
	return unidimensionalMatrix
	
def getData(Matrix, order, i, j):
	return Matrix.data[i*order+j]
	
def matrix_join(*list1):
	singleMatrix=list()
	doubleMatrix= []

	block_order= list1[0].ncols
	numMatrix = int(math.sqrt(len(list1)))

	#From N args to double matrix of matrix
	for i in xrange(0,len(list1)):
		doubleMatrix.append([])
		for x in (list1[i].data):
			doubleMatrix[i].append(x)
	
	#from matrix of matrix to single list of matrix
	for z in xrange(0, numMatrix):
		for x in xrange(0, block_order):
			for i in xrange(0,numMatrix):
				for j in xrange(0,block_order):
						singleMatrix.append(doubleMatrix[i+z*numMatrix][j+x*block_order])
	return Cannon.Matrix(int(math.sqrt(len(list1))) * block_order,singleMatrix)
	
def matrix_add(A, B):
	order = A.ncols
	result = []
	for i in xrange(0,order*order):
		result.append(A.data[i] + B.data[i])
	
	return Cannon.Matrix(order, result)
	
	
