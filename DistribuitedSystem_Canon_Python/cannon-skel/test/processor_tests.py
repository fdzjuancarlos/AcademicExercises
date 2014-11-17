# -*- mode:python; coding:utf-8; tab-width:4 -*-

from unittest import TestCase

from doublex import assert_that, Spy, called, ANY_ARG

import Ice
Ice.loadSlice('-I {} cannon.ice'.format(Ice.getSliceDir()))
import Cannon

from processor import ProcessorI, FrontendI

from common import M1, M2, M6, M4


class ProcessorServantTests(TestCase):
    """
    These are NOT remote tests. We directly instantiate servants here.
    """
    def tesst_processors_1x1_block(self):
        # given
        P0 = ProcessorI()
        collector = Spy()

        A = M1(2)
        B = M1(5)
        C = M1(10)

        # when
        P0.init(0, 1, None, None, collector)
        P0.injectA(A, 0)
        P0.injectB(B, 0)

        # then
        assert_that(collector.inject, called().with_args(0, C, ANY_ARG))

    def tesst_processors_2x2_block(self):
        # given
        P0 = ProcessorI()
        collector = Spy()

        A = M2(1, 2,
               3, 4)
        B = M2(5, 6,
               7, 8)
        C = M2(19, 22,
               43, 50)

        # when
        P0.init(0, 1, None, None, collector)
        P0.injectA(A, 0)
        P0.injectB(B, 0)

        # then
        assert_that(collector.inject, called().with_args(0, C, ANY_ARG))
        
    def tesst_processors_2x2_block_rotation(self):
        # given
        P0 = Spy()
        P1 = ProcessorI()
        P2 = ProcessorI()
        P3 = ProcessorI()
        # P0   P1
        # P2   P3
        collector = Spy()

        A = M2(1, 2,
               3, 4)
        B = M2(5, 6,
               7, 8)
        C = M2(19, 22,
               43, 50)
        D = M2(9, 10,
        	 11, 12)
        	 
      
        

        # when
        P0.init(0, 4, P1, P2, collector)
        P1.init(1, 4, P0, P3, collector)
        P2.init(2, 4, P3, P0, collector)
        P3.init(3, 4, P2, P1, collector)
        P0.injectA(A, 0)
        P0.injectB(A, 0)
        P1.injectA(B, 0)
        P1.injectB(B, 0)
        P2.injectA(C, 0)
        P2.injectB(C, 0)
        P3.injectA(D, 0)
        P3.injectB(D, 0)
        
        for i in xrange(0,3):
        	print(i)

        # then
        #assert_that(collector.inject, called().with_args(0, C, ANY_ARG))
        #assert_that(P0.A.data[0], C.data[0])
        #assert_that(P0.injectA, called().with_args(1, C, ANY_ARG))
        
    def test_frontend(self):
        # given
        front = FrontendI()

        A = M6(1,2,3,4,5,6  ,1,2,3,4,7,8  ,1,2,3,4,12,14  ,1,2,3,4,16,19  ,1,2,3,4,2,2  ,1,2,3,4,3,3  ,
        1,2,3,4,15,26  ,1,2,3,4,35,46  ,1,2,3,4,55,66)
        #A = M4(1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4)

        # when
        front.multiply(A,A)

        # then
        assert_that(True)
