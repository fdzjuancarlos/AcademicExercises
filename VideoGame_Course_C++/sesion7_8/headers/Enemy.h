
#ifndef ENEMY_H
#define ENEMY_H
#include"Entity3D.h"
#include <iostream>

class Enemy : public Entity3D{
	int _hp;
public:
	Enemy(std::string name,int x,int y,int z,int hp);
	int getHp();
};

#endif
