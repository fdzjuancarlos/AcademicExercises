#include"Entity3D.h"

//	class Entity3D{
//		Vec3 _spaceLocation;
//		std::string _name;
//	public:
//		Entity3D(std::string name, int x, int y, int z);
//		std::string getName();
//		std::string getCoords_s();
//	}

Entity3D::Entity3D(std::string name, int x, int y, int z){
	Vec3 location(x,y,z);
	_spaceLocation = location;
	_name = name;
}

std::string Entity3D::getName(){
	return _name;
}

int Entity3D::getCoordX(){
	return _spaceLocation.getX();
}
