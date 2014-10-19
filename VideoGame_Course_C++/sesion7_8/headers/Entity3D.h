
#ifndef ENTITY3D_H
#define ENTITY3D_H
#include"Vec3.h"
#include <iostream>

class Entity3D{
	Vec3 _spaceLocation;
	std::string _name;
public:
	Entity3D(std::string name, int x, int y, int z);
	std::string getName();
	int getCoordX();
};

#endif
