#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Lista.h"
using namespace std;

int getData(string dataName);

int main(int argc, char *argv[]){
	
	Lista<int>* myLista = new Lista<int>();
	int five = 5;
	int six = 6;
	int seven = 7;
	myLista->insertarInicio(five);
	myLista->insertarFinal(six);
	myLista->insertarFinal(seven);
	myLista->insertar_n(1, five);
	myLista->modificar_n(0, seven);
	int pointer = (myLista->getCabeza()->getDatos());
	std::cout << pointer << " " << myLista->getCola()->getDatos() << " " << myLista->obtenerN(1)->getDatos() << std::endl;
	
	return 0;
}

int getData(string dataName){
	
	int data;
	cout << "Introduce el valor de " << dataName << endl;
	cin >> data;
	
	return data;
}
