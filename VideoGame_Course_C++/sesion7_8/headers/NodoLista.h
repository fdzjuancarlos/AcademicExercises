
#ifndef NODOLISTA_H
#define NODOLISTA_H
#include <iostream>

template<class T>
class NodoLista {
public:
	NodoLista<T> (T datos){
		_datos = datos;
		_siguiente= NULL;
		_anterior= NULL;
	}
	NodoLista<T> (T datos, NodoLista<T>* anterior){
		_datos = datos;
		_anterior = anterior;
		anterior->setSiguiente(this);
	}
	T & getDatos (){
		return _datos;
	}
	void setDatos(T datos){
		_datos = datos;	
	}
	
	NodoLista * siguiente(){
		return _siguiente;
	}
	NodoLista * anterior(){
		return _anterior;
	}
	
	void setSiguiente(NodoLista<T>* n_siguiente){
		_siguiente = n_siguiente;
	}
	
	void setAnterior(NodoLista<T>* n_anterior){
		_anterior = n_anterior;
	}
private:
	T _datos;
	NodoLista* _siguiente;
	NodoLista* _anterior;
};


#endif
