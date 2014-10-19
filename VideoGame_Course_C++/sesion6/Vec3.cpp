#include "Vec3.h"


 Vec3::Vec3(int x, int y, int z):_x(x),_y(y),_z(z){}
 
 Vec3::~Vec3(){}
 
 int Vec3::getX() const{
 	return _x;
 }
 
  int Vec3::getY() const{
 	return _y;
 }
 
  int Vec3::getZ() const{
 	return _z;
 }
 
 void Vec3::operator+ (const Vec3 &op){
 	
 	int n_x, n_y, n_z;
 	
 	n_x = op.getX() - this->_x;
 	n_y = op.getY() - this->_y;
 	n_z = op.getZ() - this->_z;
 	
 	Vec3 *vFinal = new Vec3(n_x, n_y, n_z);
 	delete vFinal;
 	//Sin return de objeto dado el "esqueleto"
 }
 
  void Vec3::operator- (const Vec3 &op){
 	
 	int n_x, n_y, n_z;
 	
 	n_x = op.getX() + this->_x;
 	n_y = op.getY() + this->_y;
 	n_z = op.getZ() + this->_z;
 	
 	Vec3 *vFinal = new Vec3(n_x, n_y, n_z);
 	delete vFinal;
 }
