# -*- mode:python; coding:utf-8; tab-width:4 -*-

import Ice
Ice.loadSlice('-I {} cannon.ice'.format(Ice.getSliceDir()))
import Cannon

import itertools


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
