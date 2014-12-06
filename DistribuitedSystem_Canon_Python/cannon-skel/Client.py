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
			
			
		A = M4(1,  2,  3,  4, 5,  6,  7,  8, 9, 10, 11, 12, 13, 14, 15, 16)

		B = M4(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32)
        

		print(frontend.multiply(A,B))

		return 0
		



sys.exit(Client().main(sys.argv))
