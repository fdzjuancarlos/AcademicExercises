#include"Triangle.h"

Triangle::Triangle (const Vec3 &v1, const Vec3 &v2, const Vec3 &v3){
	_v1 = new Vec3;
	_v2 = new Vec3;
	_v3 = new Vec3;
	
  	*_v1 = v1;
  	*_v2 = v2;
  	*_v3 = v3;
}
  
Triangle::Triangle (const Triangle &t){
	
	_v1 = new Vec3(t.getV1().getX(), t.getV1().getY(),t.getV1().getZ());
	_v2 = new Vec3(t.getV2().getX(), t.getV2().getY(),t.getV2().getZ());
	_v3 = new Vec3(t.getV3().getX(), t.getV3().getY(),t.getV3().getZ());
}

Triangle::~Triangle (){
	delete _v1;
	delete _v2;
	delete _v3;
}

Triangle& Triangle::operator= (const Triangle &t){
	
	Vec3 
	_v1(t.getV1().getX(), t.getV1().getY(),t.getV1().getZ()),
	_v2(t.getV2().getX(), t.getV2().getY(),t.getV2().getZ()),
	_v3(t.getV3().getX(), t.getV3().getY(),t.getV3().getZ());
	
	Triangle *_triangle = new Triangle(_v1, _v2, _v3);
	return *_triangle;
}

Vec3 Triangle::getV1 () const{
  	return *_v1;
}
Vec3 Triangle::getV2 () const{
  	return *_v2;
}
Vec3 Triangle::getV3 () const{
  	return *_v3;
}
