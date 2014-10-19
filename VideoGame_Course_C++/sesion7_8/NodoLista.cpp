
#include "NodoLista.h"

NodoLista::NodoLista(T datos){
	_datos = datos;
	siguiente= NULL;
	anterior= NULL;
}

NodoLista::NodoLista(T datos, NodoLista* anterior){
	_datos = datos;
	_anterior = anterior;
	anterior->setSiguiente(this);
}

void NodoLista::setSiguiente(NodoLista* n_siguiente){
	_siguiente = n_siguiente;
}

void NodoLista::setAnterior(NodoLista* n_anterior){
	_anterior = n_anterior;
}

NodoLista* NodoLista::siguiente(){
	return _siguiente;
}

NodoLista* NodoLista::anterior(){
	return _anterior;
}

T& NodoLista::getDatos(){
	return _datos;
}

void NodoLista::setDatos(T datos){
	
}
