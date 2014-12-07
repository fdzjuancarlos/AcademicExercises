#!/usr/bin/make -f
# -*- mode:makefile -*-


all: run-server

run-processor: 
	for number in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 ; do \
		./processor.py --Ice.Config=processor.config& \
	done

run-collector:
	python collector.py --Ice.Config=collector.config
	
run-frontend:
	python frontend.py --Ice.Config=frontend.config
	
run-test:
	nosetests test/
	
clean: killprocessors
	rm processorProxy
	
killprocessors:	
	killall processor.py



   

