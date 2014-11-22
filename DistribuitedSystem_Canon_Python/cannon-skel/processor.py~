#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-

import sys

import Ice
Ice.loadSlice('-I {} cannon.ice'.format(Ice.getSliceDir()))
import Cannon
from matrix_utils import matrix_multiply
from matrix_utils import printMatrix
from Queue import Queue
from copy import copy, deepcopy

class CollectorI(Cannon.Collector):
	def inject(self, index, M, current=None):
		printMatrix(M)
		
  
class FrontendI(Cannon.Frontend):
	def multiply(self, A,B):
		self.numMatrix = A.ncols/2
		#A Matrix
		allMatrix = [[[] for x in range(self.numMatrix)] for x in range(self.numMatrix)] 
		for i in xrange(0,self.numMatrix):
			for k in xrange(0, self.numMatrix):
				newMatrix = []
				for j in xrange(0,2):
					for m in xrange(0,2):
						newMatrix.append(self.getData(A,A.ncols,j+i*2,m+k*2))
				allMatrix[i][k]=newMatrix

		for i in xrange(0,self.numMatrix):
			for j in xrange(0,i):
				temporal = deepcopy(allMatrix)
				for k in xrange(0,self.numMatrix):
					if k == 0:
						m=k
						allMatrix[i][self.numMatrix-1-m] = temporal[i][m]
					else:
						m=self.numMatrix-k
						allMatrix[i][self.numMatrix-1-k] = temporal[i][m]
		#B Matrix
		BallMatrix = [[[] for x in range(self.numMatrix)] for x in range(self.numMatrix)] 
		for i in xrange(0,self.numMatrix):
			for k in xrange(0, self.numMatrix):
				newMatrix = []
				for j in xrange(0,2):
					for m in xrange(0,2):
						newMatrix.append(self.getData(B,B.ncols,j+i*2,m+k*2))
				BallMatrix[i][k]=newMatrix

		for i in xrange(0,self.numMatrix):
			for j in xrange(0,i):
				temporal = deepcopy(BallMatrix)
				for k in xrange(0,self.numMatrix):
					if k == 0:
						m=k
						BallMatrix[self.numMatrix-1-m][i] = temporal[m][i]
					else:
						m=self.numMatrix-k
						BallMatrix[self.numMatrix-1-k][i] = temporal[m][i]
						
				
						
				
	
	def getData(self, Matrix, order, i, j):
		return Matrix.data[i*order+j]


class Job(object):
    def __init__(self, kindOfMatrix , Matrix, step):
        self.kindOfMatrix = kindOfMatrix
        self.Matrix = Matrix
        self.step = step

    def execute(self, processor):
        if self.kindOfMatrix == 'A':
        	processor.injectA(self.Matrix, self.step)
        else:
        	processor.injectB(self.Matrix, self.step)
	

class ProcessorI(Cannon.Processor):
	A= None
	B= None
	
    def __init__(self):
        self.work_queue = Queue()
	
    def init(self, index, order, above, left, target, current=None):
    	self.actualStep = 0
    	self.index = index
    	self.maximumStep = order/2
    	self.target = target
    	self.above = above
    	self.left = left
        pass
        
    def successMultiplication(self, step):
    	result = matrix_multiply(self.A,self.B)
    	#self.target.inject(step, result)
    	if self.actualStep < self.maximumStep -1:
    		self.left.injectA(self.A, step+1)
    		self.above.injectB(self.B, step+1)
    	else:
    		self.target.inject(step, result)
    	self.A = None
    	self.B = None
    	self.actualStep = self.actualStep +1
    	while not self.work_queue.empty():
    		job = self.work_queue.get()
    		self.work_queue.task_done()
    		job.execute(self)

    def injectA(self, A, step, current=None):
    	if self.actualStep == step:
			if self.B is not None:
				self.A = A
				self.successMultiplication(step)
			else:
				self.A = A
		else:
			self.work_queue.put(Job('A',A, step))
			

    def injectB(self, B, step, current=None):
    	if self.actualStep == step:
			if self.A is not None:
				self.B = B
				self.successMultiplication(step)
			else:
				self.B = B
		else:
			self.work_queue.put(Job('B',B, step))


class Server(Ice.Application):
    def run(self, args):
        broker = self.communicator()
        servant = ProcessorI()
        collector = CollectorI()

        adapter = broker.createObjectAdapter('ProcessorAdapter')
        collectorAdapter = broker.createObjectAdapter('CollectorAdapter')
        
        proxy = adapter.addWithUUID(servant)
        newProxy = collectorAdapter.addWithUUID(collector)

        print('processor ready: "{}"'.format(proxy))
        print('collector ready: "{}"'.format(newProxy))
		
		collectorAdapter.activate()
        adapter.activate()
        self.shutdownOnInterrupt()
        broker.waitForShutdown()


if __name__ == '__main__':
    app = Server()
    sys.exit(app.main(sys.argv))
