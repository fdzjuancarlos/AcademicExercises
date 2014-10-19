
#include"Lista.h"


//	class Lista {
//	public:
//	  Lista();
//	  ~Lista();
//	  NodoLista<T>* getCabeza ();
//	  NodoLista<T>* getCola();
//	  void insertarFinal (T datos);
//	  void insertarInicio (T datos);
//	  void insertar_n(int n);
//	  void eliminar_n(int n);
//	  void modificar_n(T datos);
//	  // Resto funcionalidad...
//	private:
//	  NodoLista<T> *_cabeza;
//	  NodoLista<T> *_cola;
//	};


Lista::Lista(){
	_cabeza=NULL;
	_cola=NULL;
}

Lista::~Lista(){
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

NodoLista<T>* Lista::getCabeza(){
	return _cabeza;
	// if null throw exception
}

NodoLista<T>* Lista::getCola(){
	return _cola;
}

void Lista::insertarFinal(T datos){
	NodoLista<T>* nuevoNodo = new NodoLista(datos, _cola);
	_cola = nuevoNodo;
}

void Lista::insertarInicio(T datos){
	if(_cabeza!=NULL){
		NodoLista<T>* nuevoNodo = new NodoLista(datos);
		_cabeza->setAnterior(nuevoNodo);
		_cabeza = nuevoNodo;
	}
}

void Lista::insertar_n(int n, T datos){
	if(n==0)
		insertarInicio(datos);
	else{
		NodoLista<T>* iterator = obtenerN(n);
		NodoLista<T>* nuevoNodo = new NodoLista<T>(datos, iterator->anterior());
		iterator->setAnterior(nuevoNodo);
	}
}

void Lista::eliminar_n(int n){
	NodoLista<T>* iterator = obtenerN(n);
	NodoLista<T>* anteriorNodo = iterator->anterior();
	NodoLista<T>* siguienteNodo = iterator->siguiente();
	anteriorNodo->setSiguiente(siguienteNodo);
	siguienteNodo->setAnterior(anteriorNodo);
	delete iterator;
}

NodoLista<T>* Lista::obtenerN(int n){
	NodoLista<T>* iterator=_cabeza;
	for (unsigned int i = 0; i < n; i += 1){ //if null throw exception
		iterator=iterator->siguiente();
	}
	return iterator;
}

void Lista::modificar_n(int n,T datos){
	obtenerN(n)->setDatos(datos);
}













