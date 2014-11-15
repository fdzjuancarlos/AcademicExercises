#!/usr/bin/python
# -*- mode:python; coding: utf-8 -*-

import sys
import Ice
Ice.loadSlice('-I {} cannon.ice'.format(Ice.getSliceDir()))
import Cannon


class Client(Ice.Application):
	def run(self, argv):
		A = Cannon.Matrix(3,list([1,2,3,4,5,6,7,8,9]))
		proxy = self.communicator().stringToProxy(argv[1])
		
		newProxy = self.communicator().stringToProxy(argv[2])
		
		processor = Cannon.ProcessorPrx.checkedCast(proxy)
		collector = Cannon.CollectorPrx.checkedCast(newProxy)

		if not processor:
			raise RuntimeError('Invalid proxy')
		
		print("antes de init")
		processor.init(1,1,None,None,collector)
		print("antes de injectA")
		processor.injectA(A,0)
		print("antes de injectB")
		processor.injectB(A,0)
		#collector.inject(2, A)

		return 0
		



sys.exit(Client().main(sys.argv))
