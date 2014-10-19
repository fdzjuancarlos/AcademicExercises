# -*- mode:make -*-

CC=g++
CXXFLAGS=-Wall -Werror -Iheaders
LDFLAGS=-L.
LDLIBS=


all: main

main:
	g++ $(CXXFLAGS) -o main Vec3.cpp Entity3D.cpp Player.cpp Enemy.cpp main.cpp
	
nodo:
	g++ $(CXXFLAGS) -o main NodoLista.cpp

test:
	./main


clean:
	$(RM) *.o *.a main *~ headers/*~
