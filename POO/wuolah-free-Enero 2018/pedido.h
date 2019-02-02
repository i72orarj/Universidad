// pedido.h
// Cabecera de la clase pedido
#ifndef PEDIDO_H
#define PEDIDO_H

#include <list>
#include "mesa.h"

using namespace std;

class Pedido{
private:
	list <Mesa> mesas_;
public: 
	inline Pedido(){};
	inline void addPedido(Mesa mesa) {mesas_.push_back(mesa);}
	inline int size() const {return mesas_.size();}
	bool deletePedido(string modelo);
	bool deletePedido(Mesa mesa);
	void write();
};

#endif