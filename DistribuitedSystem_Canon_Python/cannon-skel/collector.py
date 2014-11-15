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
