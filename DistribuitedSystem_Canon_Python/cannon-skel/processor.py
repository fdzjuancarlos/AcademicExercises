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
    	self.result = None
        pass
        
    def successMultiplication(self, step):
    	self.result = matrix_multiply(self.A,self.B)
    	if self.actualStep < self.maximumStep -1:
    		self.left.injectA(self.A, step+1)
    		self.above.injectB(self.B, step+1)
    	else:
    		print(step)
    		print(self.result)
    		self.target.inject(step, self.result)
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

        adapter = broker.createObjectAdapter('ProcessorAdapter')
        
        proxy = adapter.addWithUUID(servant)

        print('processor ready: "{}"'.format(proxy))
		
        adapter.activate()
        self.shutdownOnInterrupt()
        broker.waitForShutdown()


if __name__ == '__main__':
    app = Server()
    sys.exit(app.main(sys.argv))
