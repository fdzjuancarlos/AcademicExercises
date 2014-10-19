
#ifndef NODOLISTA_H
#define NODOLISTA_H
template<class T>
class NodoLista {
public:
	NodoLista (T datos);
	NodoLista (T datos, NodoLista* anterior);
	T & getDatos ();
	void setDatos(T datos);
	NodoLista * siguiente();
	NodoLista * anterior();
	void setSiguiente(NodoLista* n_siguiente);
	void setAnterior(NodoLista* n_anterior);
private:
	T _datos;
	NodoLista* _siguiente;
	NodoLista* _anterior;
};


#endif
