#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-
import sys

import Ice
Ice.loadSlice('-I {} cannon.ice'.format(Ice.getSliceDir()))
import Cannon
from matrix_utils import matrix_multiply
from matrix_utils import printMatrix, list_split, matrix_horizontal_shift, matrix_vertical_shift, matrix_split
from collector import CollectorI
from common import M4, M1
import math

class Broker(object):
    def __init__(self, properties=None):
        properties = properties or []

        data = Ice.InitializationData()
        data.properties = Ice.createProperties()

        for p in properties:
            data.properties.setProperty(p[0], p[1])

        self.communicator = Ice.initialize(data)
        self.adapter = self.communicator.createObjectAdapterWithEndpoints('Adapter', 'tcp')
        self.adapter.activate()

    def add_servant(self, servant, iface):
        proxy = self.adapter.addWithUUID(servant)
        return iface.uncheckedCast(proxy)

    def shutdown(self):
        self.adapter.deactivate()
        self.communicator.shutdown()

class FrontendI(Cannon.Frontend):
	def __init__(self, matrixProcessors):
		self.matrixProcessors = matrixProcessors
		self.organizedMProcessors = None
		self.target = None
		self.orderMatrixProcessors= int(math.sqrt(len(self.matrixProcessors)))
		self.organizedMProcessors = list_split(self.matrixProcessors, self.orderMatrixProcessors)

		#Creating Collector
		self.broker = Broker([
            ["Ice.ThreadPool.Server.Size", "20"],
            ["Ice.ThreadPool.Client.Size", "20"]])
		self.collector_servant = CollectorI(self.orderMatrixProcessors)
        self.target = self.broker.add_servant(self.collector_servant, Cannon.CollectorPrx)
		
	def multiply(self, A,B, current=None):

		self.init_processors()
		self.load_processors(A,B)
		return self.collector_servant.get_result()
		
	
	def load_collector(self, collector):
		self.target = collector
     
	def init_processors(self):
		self.orderMatrixProcessors = int(math.sqrt(len(self.matrixProcessors)))
     	
		for i in xrange(0,self.orderMatrixProcessors):
			for k in xrange(0,self.orderMatrixProcessors):
				leftOffset= self.orderMatrixProcessors-1-k
				aboveOffset= self.orderMatrixProcessors-1-i
				if not k==0:
					leftOffset = k-1
				if not i==0:
					aboveOffset = i-1
				self.organizedMProcessors[i][k].init(i*self.orderMatrixProcessors+k, self.orderMatrixProcessors, self.organizedMProcessors[aboveOffset][k], self.organizedMProcessors[i][leftOffset], self.target)
				
						
	def load_processors(self,A, B):
		orderMatrixProcessors = int(math.sqrt(len(self.matrixProcessors)))
		#orderMatrixProcessors = len(self.matrixProcessors)
		block_order= A.ncols/orderMatrixProcessors
		
		
		A_shifted= matrix_horizontal_shift(A, block_order)
		B_shifted= matrix_vertical_shift(B, block_order)
		
		A_splitted= matrix_split(A_shifted,block_order)
		B_splitted= matrix_split(B_shifted,block_order)
		
		
		for i in xrange(0,orderMatrixProcessors):
			for j in xrange(0,orderMatrixProcessors):
				self.organizedMProcessors[i][j].injectA(A_splitted[i*orderMatrixProcessors+j],0)
				self.organizedMProcessors[i][j].injectB(B_splitted[i*orderMatrixProcessors+j],0)
				#self.matrixProcessors[i][j].injectA(A_splitted[i*orderMatrixProcessors+j],0)
				#self.matrixProcessors[i][j].injectB(B_splitted[i*orderMatrixProcessors+j],0)
		
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
		frontend.init_processors()
        
        
		newProxy = frontendAdapter.add(frontend, Ice.Identity("frontend","cannon"))

		print('frontend ready: "{}"'.format(newProxy))
       
		
		frontendAdapter.activate()
		self.shutdownOnInterrupt()
		broker.waitForShutdown()


if __name__ == '__main__':
    app = Server()
    sys.exit(app.main(sys.argv))
		
		
				
