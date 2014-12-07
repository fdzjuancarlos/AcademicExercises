#!/usr/bin/python
# -*- mode:python; coding: utf-8 -*-

import sys
import Ice
Ice.loadSlice('-I {} cannon.ice'.format(Ice.getSliceDir()))
import Cannon
from common import M4


class Client(Ice.Application):
	def run(self, argv):
		proxy = self.communicator().stringToProxy("cannon/frontend -t -e 1.1:tcp -h 127.0.0.1 -p 4059")
		frontend = Cannon.FrontendPrx.checkedCast(proxy)
			
			
		A = M400()

		B = M400()
        

		print(frontend.multiply(A,B))

		return 0
		
	
def M400():
	
	data = []
	
	for i in xrange(0,400*400):
		data.append(i)
		
	return Cannon.Matrix(400, data)
		



sys.exit(Client().main(sys.argv))
