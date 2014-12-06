#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-

import sys

import Ice
Ice.loadSlice('-I {} cannon.ice'.format(Ice.getSliceDir()))
import Cannon
from matrix_utils import matrix_multiply
from matrix_utils import printMatrix, matrix_join
import dummy_threading
import threading
import time

class CollectorI(Cannon.Collector):
	def inject(self, index, M, current=None):
		self.mutex.acquire()
		self.matrix.append((index, M))
		self.matrix =sorted(self.matrix, key=lambda tup: tup[0])
		if (len(self.matrix) == self.totalOrder):
			listMatrix = []
			for i in self.matrix:
				listMatrix.append(i[1])
			self.matrix= matrix_join(*listMatrix)
			self.isReady.release()
		self.mutex.release()
		
	def __init__(self, totalOrder):
		self.totalOrder = totalOrder*totalOrder
		self.matrix = list()
		self.isReady = threading.Semaphore(0)
		self.mutex = threading.Lock()

    def get_result(self):
    	#fix with asynchronous

    	self.isReady.acquire()
		result = self.matrix
		self.matrix = list()
    		
    	return result
    		

class Server(Ice.Application):
    def run(self, args):
        broker = self.communicator()
        collector = CollectorI()

        collectorAdapter = broker.createObjectAdapter('CollectorAdapter')
        
        newProxy = collectorAdapter.addWithUUID(collector)

        print('collector ready: "{}"'.format(newProxy))
		
		collectorAdapter.activate()
        self.shutdownOnInterrupt()
        broker.waitForShutdown()


if __name__ == '__main__':
    app = Server()
    sys.exit(app.main(sys.argv))
