#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-

import sys

import Ice
Ice.loadSlice('-I {} cannon.ice'.format(Ice.getSliceDir()))
import Cannon
from matrix_utils import matrix_multiply
from matrix_utils import printMatrix

class CollectorI(Cannon.Collector):
	def inject(self, index, M, current=None):
		print("gonna print")
		printMatrix(M)
	

class ProcessorI(Cannon.Processor):
	A= None
	B= None
    def init(self, index, order, above, left, target, current=None):
    	self.target = target
        pass

    def injectA(self, A, step, current=None):
    	if self.B is not None:
    		result = matrix_multiply(A,self.B)
    		self.target.inject(step, result)
    		self.A = None
    		self.B = None
    	else:
    		self.A = A
    		print("self.A = A")
        pass

    def injectB(self, B, step, current=None):
		if self.A is not None:
			print("bEFORE MULTIPLY")
			result = matrix_multiply(self.A,B)
			print("bEFORE INJECT TO COLLECTOR")
			print (self.target is None)
			self.target.inject(1, result)
			print("antes de los nones")
    		self.A = None
    		self.B = None
    	else:
			self.B = B
			print("self.B = B")
        pass


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
