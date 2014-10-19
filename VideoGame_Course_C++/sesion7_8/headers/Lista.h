


#ifndef LISTA_H
#define LISTA_H

#include "NodoLista.h"
#include "ListException.h"

template<class T>
class Lista {
public:
	Lista(){
		_cabeza=NULL;
		_cola=NULL;
	}
	~Lista(){
		NodoLista<T>* toDelete;
		NodoLista<T>* iterator;
		if(_cabeza!=NULL){
			iterator = _cabeza;
			while(iterator != NULL){
				toDelete= iterator;
				iterator = iterator->siguiente();
				delete toDelete;
			}
		}
	}
	
	NodoLista<T>* getCabeza (){
		if(_cabeza == NULL){
			std::string problem("Exception: Empty List");
			throw ListException(problem);
			}
		return _cabeza;
		// if null throw exception
	}
	
	NodoLista<T>* getCola(){
		if(_cabeza == NULL){
			std::string problem("Exception: Empty List");
			throw ListException(problem);
		}
		return _cola;
	}
	
	NodoLista<T>* obtenerN(int n){
		NodoLista<T>* iterator=_cabeza;
		for (unsigned int i = 0; i < n; i += 1){
			iterator=iterator->siguiente();
			if(iterator==NULL){
				std::string problem("Exception: Out of Bounds");
				throw ListException(problem);
			}
		}
		return iterator;
	}
	
	void insertarFinal (T datos){
		if(_cabeza!=NULL){
			if(_cola!=NULL){
				NodoLista<T>* nuevoNodo = new NodoLista<T>(datos, _cola);
				_cola = nuevoNodo;
			}else{
				NodoLista<T>* nuevoNodo = new NodoLista<T>(datos, _cabeza);
				_cola = nuevoNodo;
			}	
		}else{
			NodoLista<T>* nuevoNodo = new NodoLista<T>(datos);
			_cabeza = nuevoNodo;
		}
	}
	
	void insertarInicio (T datos){
		NodoLista<T>* nuevoNodo = new NodoLista<T>(datos);
		if(_cabeza!=NULL){
			_cabeza->setAnterior(nuevoNodo);
			_cabeza = nuevoNodo;
		}else
			_cabeza = nuevoNodo;
		
	}
	void insertar_n(int n, T datos){
		if(n==0)
			insertarInicio(datos);
		else{
			NodoLista<T>* iterator = obtenerN(n);
			NodoLista<T>* nuevoNodo = new NodoLista<T>(datos, iterator->anterior());
			iterator->setAnterior(nuevoNodo);
		}
	}
	
	void eliminar_n(int n){
		NodoLista<T>* iterator = obtenerN(n);
		NodoLista<T>* anteriorNodo = iterator->anterior();
		NodoLista<T>* siguienteNodo = iterator->siguiente();
		anteriorNodo->setSiguiente(siguienteNodo);
		siguienteNodo->setAnterior(anteriorNodo);
		delete iterator;
	}
	
	void modificar_n(int n,T datos){
		obtenerN(n)->setDatos(datos);
	}
	
private:
  NodoLista<T> *_cabeza;
  NodoLista<T> *_cola;
};


#endif
