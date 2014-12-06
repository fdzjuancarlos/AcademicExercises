#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-

import sys

import Ice
Ice.loadSlice('-I {} cannon.ice'.format(Ice.getSliceDir()))
import Cannon
from matrix_utils import matrix_multiply, matrix_add
from matrix_utils import printMatrix
import Queue
from copy import copy, deepcopy
import time
  



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
	actualStep = None
	
    def __init__(self):
        self.work_queue = Queue.PriorityQueue()
	
    def init(self, index, order, above, left, target, current=None):
    	self.actualStep = 0
    	self.index = index
    	self.maximumStep = order
    	self.target = target
    	self.above = above
    	self.left = left
    	self.result = None
        
    def successMultiplication(self, step):
		if self.result:
    		self.result = matrix_add(self.result,matrix_multiply(self.A,self.B))
		else:
			self.result = matrix_multiply(self.A,self.B)
    	self.actualStep = self.actualStep +1
    	if self.actualStep < self.maximumStep :
    		self.left.injectA(self.A, self.actualStep)
    		self.A = None
    		self.above.injectB(self.B, self.actualStep)
			self.B = None
    	else:
    		self.target.inject(self.index, self.result)
		
		stop = 0
    	while not self.work_queue.empty() and stop < 5:
    		job = self.work_queue.get()
    		job[1].execute(self)
			stop = stop +1
    		self.work_queue.task_done()

    def injectA(self, A, step, current=None):
    	if self.actualStep == step:
			if self.B is not None:
				self.A = A
				self.successMultiplication(step)
			else:
				self.A = A
		else:
			self.work_queue.put((step,Job('A',A, step)))
			

    def injectB(self, B, step, current=None):
    	if self.actualStep == step:
			if self.A is not None:
				self.B = B
				self.successMultiplication(step)
			else:
				self.B = B
		else:
			self.work_queue.put((step,Job('B',B, step)))


class Server(Ice.Application):
    def run(self, args):
        broker = self.communicator()
        servant = ProcessorI()

        adapter = broker.createObjectAdapter('ProcessorAdapter')
        
        proxy = adapter.addWithUUID(servant)

        print('processor ready: "{}"'.format(proxy))

		f=open('processorProxy', 'a')
		f.write('"{}" '.format(proxy))
		f.close()
        adapter.activate()
        self.shutdownOnInterrupt()
        broker.waitForShutdown()


if __name__ == '__main__':
    app = Server()
    sys.exit(app.main(sys.argv))
