#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Lista.h"
#include "Entity3D.h"
#include "Player.h"
#include "Enemy.h"
using namespace std;

int getData(string dataName);

int main(int argc, char *argv[]){
	
	Lista<int>* myLista = new Lista<int>();
	int five = 5;
	int six = 6;
	int seven = 7;
	try{
	myLista->getCabeza()->getDatos();
	myLista->insertarInicio(five);
	myLista->insertarFinal(six);
	myLista->insertarFinal(seven);
	myLista->insertar_n(6, five);
	myLista->modificar_n(0, seven);
	int pointer = (myLista->getCabeza()->getDatos());
	std::cout << pointer << " " << myLista->getCola()->getDatos() << " " << myLista->obtenerN(1)->getDatos() << std::endl;
	}catch(ListException e){
		std::cout << e.getReason() << std::endl;
	}
	std::string name("Bartolo");
	std::string weaponName("Colisionador de Hadrones");
	
	Player newPlayer(name, 3, 4, 5, weaponName);
	std::cout << newPlayer.getCoordX() << " y tiene el arma " << newPlayer.getWeaponName() << std::endl;
	
	std::string enemyName("Troll de las cavernas");
	
	Entity3D* p_entity;
	Enemy troll(enemyName, 3, 3, 3, 15);
	p_entity = &troll;
	std::cout << p_entity->getName() << " obtenido a través de polimorfismo" << std::endl;
	
	Lista<Entity3D*>* listaClases = new Lista<Entity3D*>;
	listaClases->insertarInicio(&troll);
	std::cout << "Nombre: " <<listaClases->getCabeza()->getDatos()->getName()  << " obtenido a través de lista de apuntadores con polimorfismo" << std::endl;
	
	return 0;
}

int getData(string dataName){
	
	int data;
	cout << "Introduce el valor de " << dataName << endl;
	cin >> data;
	
	return data;
}
