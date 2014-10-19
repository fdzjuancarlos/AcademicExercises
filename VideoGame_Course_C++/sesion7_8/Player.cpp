#include "Player.h"

//	class Player : public Entity3D{
//		std::string _wepaonName;
//	public:
//		Player(std::string name,int x,int y,int z,std::string weaponName)
//		std::string getWeaponName();
//	};

Player::Player(std::string name,int x,int y,int z,std::string weaponName) : Entity3D(name,x,y,z){
	_weaponName = weaponName;
}

std::string Player::getWeaponName(){
	return _weaponName;
}
