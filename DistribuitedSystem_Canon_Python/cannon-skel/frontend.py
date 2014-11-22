import sys

import Ice
Ice.loadSlice('-I {} cannon.ice'.format(Ice.getSliceDir()))
import Cannon
from matrix_utils import matrix_multiply
from matrix_utils import printMatrix, list_split, matrix_horizontal_shift, matrix_vertical_shift, matrix_split
import math

class FrontendI(Cannon.Frontend):
	def __init__(self, matrixProcessors):
		self.matrixProcessors = matrixProcessors
		
		
	def multiply(self, A,B, current=None):
		pass
		
	

     
	def init_processors(self):
		self.orderMatrixProcessors = int(math.sqrt(len(self.matrixProcessors)))
		self.matrixProcessors = list_split(self.matrixProcessors, self.orderMatrixProcessors)
     	
		for i in xrange(0,self.orderMatrixProcessors):
			for k in xrange(0,self.orderMatrixProcessors):
				leftOffset= self.orderMatrixProcessors-1-k
				aboveOffset= self.orderMatrixProcessors-1-i
				if not k==0:
					leftOffset = k-1
				if not i==0:
					aboveOffset = i-1
				self.matrixProcessors[i][k].init(i*self.orderMatrixProcessors+k, self.orderMatrixProcessors, self.matrixProcessors[aboveOffset][k], self.matrixProcessors[i][leftOffset], None)
						
	def load_processors(self,A, B):
		orderMatrixProcessors = int(math.sqrt(len(self.matrixProcessors)))
		block_order= A.ncols/orderMatrixProcessors
		
		A_shifted= matrix_horizontal_shift(A, block_order)
		B_shifted= matrix_vertical_shift(B, block_order)
		
		A_splitted= matrix_split(A_shifted,block_order)
		B_splitted= matrix_split(B_shifted,block_order)
		
		for i in xrange(0,orderMatrixProcessors):
			for j in xrange(0,orderMatrixProcessors):
				self.matrixProcessors[i*orderMatrixProcessors+j].injectA(A_splitted[i*orderMatrixProcessors+j],0)
				self.matrixProcessors[i*orderMatrixProcessors+j].injectB(B_splitted[i*orderMatrixProcessors+j],0)
		
		
		
				
