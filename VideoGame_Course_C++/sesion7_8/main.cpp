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
	myLista->insertarInicio(five);
	int pointer = (myLista->getCabeza()->getDatos());
	std::cout << pointer << std::endl;
	
	return 0;
}

int getData(string dataName){
	
	int data;
	cout << "Introduce el valor de " << dataName << endl;
	cin >> data;
	
	return data;
}
