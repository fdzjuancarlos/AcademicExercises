#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-
import sys

import Ice
Ice.loadSlice('-I {} cannon.ice'.format(Ice.getSliceDir()))
import Cannon
from matrix_utils import matrix_multiply
from matrix_utils import printMatrix, list_split, matrix_horizontal_shift, matrix_vertical_shift, matrix_split
from collector import CollectorI
import math

class FrontendI(Cannon.Frontend):
	def __init__(self, matrixProcessors):
		self.matrixProcessors = matrixProcessors
		
		
	def multiply(self, A,B, current=None):
		pass
		
	

     
	def init_processors(self):
		self.orderMatrixProcessors = int(math.sqrt(len(self.matrixProcessors)))
		self.matrixProcessors = list_split(self.matrixProcessors, self.orderMatrixProcessors)
		self.collector = CollectorI()
     	
		for i in xrange(0,self.orderMatrixProcessors):
			for k in xrange(0,self.orderMatrixProcessors):
				leftOffset= self.orderMatrixProcessors-1-k
				aboveOffset= self.orderMatrixProcessors-1-i
				if not k==0:
					leftOffset = k-1
				if not i==0:
					aboveOffset = i-1
				self.matrixProcessors[i][k].init(i*self.orderMatrixProcessors+k, self.orderMatrixProcessors, self.matrixProcessors[aboveOffset][k], self.matrixProcessors[i][leftOffset], self.collector)
						
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
		
class Server(Ice.Application):
    def run(self, argv):
        broker = self.communicator()
        
		proxy = [self.communicator().stringToProxy(argv[1]),self.communicator().stringToProxy(argv[2]),
				self.communicator().stringToProxy(argv[3]),self.communicator().stringToProxy(argv[4])]
		
		processor = []
		for i in proxy:
			processor.append(Cannon.ProcessorPrx.checkedCast(i))
        
        
        frontend = FrontendI(processor)

        frontendAdapter = broker.createObjectAdapter('FrontendAdapter')
        
        
        
        newProxy = frontendAdapter.add(servant, Ice.Identity("frontend","cannon"))

        print('frontend ready: "{}"'.format(newProxy))
		
		frontendAdapter.activate()
        self.shutdownOnInterrupt()
        broker.waitForShutdown()


if __name__ == '__main__':
    app = Server()
    sys.exit(app.main(sys.argv))
		
		
				
