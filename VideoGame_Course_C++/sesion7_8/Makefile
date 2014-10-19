# -*- mode:make -*-

CC=g++
CXXFLAGS=-Wall -Werror -Iheaders
LDFLAGS=-L.
LDLIBS=


all: main

main:
	g++ $(CXXFLAGS) -o main Vec3.cpp Triangle.cpp main.cpp

test:
	./main


clean:
	$(RM) *.o *.a main *~
