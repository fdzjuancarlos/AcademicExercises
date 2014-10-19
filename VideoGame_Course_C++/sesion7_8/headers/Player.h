
#ifndef PLAYER_H
#define PLAYER_H
#include"Entity3D.h"
#include <iostream>

class Player : public Entity3D{
	std::string _weaponName;
public:
	Player(std::string name,int x,int y,int z,std::string weaponName);
	std::string getWeaponName();
};

#endif
