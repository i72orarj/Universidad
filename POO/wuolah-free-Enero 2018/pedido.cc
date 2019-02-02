// pedido.cc
// Cuerpo de la clase pedido

#include <list>
#include <fstream>
#include <string>
#include "pedido.h"

using namespace std;

bool Pedido::deletePedido(string modelo) {
	list <Mesa> :: iterator i;

	for(i=mesas_.begin(); i!=mesas_.end(); i++)
		if(modelo==(*i).getModelo()) {
			mesas_.erase(i);
			return true;
		}
	return false;
}

bool Pedido::deletePedido(Mesa mesa) {
	list <Mesa> :: iterator i;

	for(i=mesas_.begin(); i!=mesas_.end(); i++)
		if(mesa.getModelo()==(*i).getModelo()) {
			mesas_.erase(i);
			return true;
		}
	return false;
}

void Pedido::write() {
	ofstream f1;
	f1.open("salida.txt");

	list <Mesa> :: iterator i;
	int pos=1;

	for(i=mesas_.begin(); i!=mesas_.end(); i++) {
		f1 << pos << "," << (*i).getId() << "," << (*i).getNombre() << ","
		   << (*i).getModelo() << "," << (*i).getMaterial() << endl;
		pos++;
	}
}
