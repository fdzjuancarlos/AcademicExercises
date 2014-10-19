#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Triangle.h"
using namespace std;

int getData(string dataName);

int main(int argc, char *argv[]){
	
	int x, y, z;
	while(true){
	x= getData("x de para el vector 1 ");
	y= getData("y de para el vector 1 ");
	z= getData("z de para el vector 1 ");
	Vec3 v1(x,y,z);
	x= getData("x de para el vector 2 ");
	y= getData("y de para el vector 2 ");
	z= getData("z de para el vector 2 ");
	Vec3 v2(x,y,z);
	x= getData("x de para el vector 3 ");
	y= getData("y de para el vector 3 ");
	z= getData("z de para el vector 3 ");
	Vec3 v3(x,y,z);
	Triangle myTriangle (v1,v2,v3);
	cout << "v1 x: " <<myTriangle.getV1().getX() << endl; 
	cout << "v1 y: " <<myTriangle.getV1().getY() << endl; 
	cout << "v1 z: " <<myTriangle.getV1().getZ() << endl; 
	cout << "v2 x: " <<myTriangle.getV2().getX() << endl; 
	cout << "v2 y: " <<myTriangle.getV2().getY() << endl; 
	cout << "v2 z: " <<myTriangle.getV2().getZ() << endl; 
	cout << "v3 x: " <<myTriangle.getV3().getX() << endl; 
	cout << "v3 y: " <<myTriangle.getV3().getY() << endl; 
	cout << "v3 z: " <<myTriangle.getV3().getZ() << endl; 
	}
	
	return 0;
}

int getData(string dataName){
	
	int data;
	cout << "Introduce el valor de " << dataName << endl;
	cin >> data;
	
	return data;
}
