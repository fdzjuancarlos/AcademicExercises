#!/usr/bin/make -f
# -*- mode:makefile -*-


all: run-server

run-server: 
	./processor.py --Ice.Config=processor.config

	
run-test:
	python -m unittest processor_tests

