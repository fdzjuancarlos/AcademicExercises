#!/usr/bin/make -f
# -*- mode:makefile -*-

include ./cpp-common.mk

APP=Canon
STUBS=$(addprefix $(APP), .h .cpp)

all: Server Client

Server: Server.o $(APP)I.o $(APP).o
Server-UUID: Server-UUID.o $(APP)I.o $(APP).o
Client: Client.o $(APP).o

Server.cpp Client.cpp: $(STUBS)

%.cpp %.h: %.ice
	slice2cpp $<

dist:
	mkdir dist

gen-dist: all dist
	cp Client Server dist/
	icepatch2calc dist/

clean:
	$(RM) Server Client $(STUBS) *.o *~
	$(RM) *.bz2 IcePatch2.sum
	$(RM) -r dist

calc:
	icepatch2calc .

run-server: Server
	./Server --Ice.Config=Server.config

run-client: Client
	./Client "collector1 -t -e 1.1:tcp -h 10.211.55.9 -p 3030" "processor1 -t -e 1.1:tcp -h 10.211.55.9 -p 3031"

