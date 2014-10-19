
+ Inclusión de las operaciones insertar_n, eliminar_n y modificar_n, que insertar, elimina y modifica un elemento en la posición n, respectivamente.

#ifndef LISTA_H
#define LISTA_H

#include "NodoLista.h"


template<class T>
class Lista {
public:
  Lista();
  ~Lista();
  NodoLista<T>* getCabeza ();
  NodoLista<T>* getCola();
  NodoLista<T>* obtenerN(int n);
  void insertarFinal (T datos);
  void insertarInicio (T datos);
  void insertar_n(int n, T datos);
  void eliminar_n(int n);
  void modificar_n(int n,T datos);
  // Resto funcionalidad...
private:
  NodoLista<T> *_cabeza;
  NodoLista<T> *_cola;
};


#endif
