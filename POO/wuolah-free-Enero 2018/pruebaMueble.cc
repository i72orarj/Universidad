// prueba.cc
// Programa principal que prueba la funcionalidad de 
// la clase mueble, mesa, pedido.

// g++ pruebaMueble.cc mueble.cc mesa.cc pedido.cc -Wall

#include <iostream>

#include "mueble.h"
#include "mesa.h"
#include "pedido.h"

using namespace std;

int main(int argc, char const *argv[]) {
	Mueble m1(1111);

	cout << m1.getDatos() << endl << endl;

	m1.setNombre("m1");
	m1.setModelo("model1");
	m1.setFecha("01/01/99");
	m1.setColor("Amarillo");

	cout << m1.getDatos() << endl << endl;

	m1.setNombre("");
	m1.setModelo("");
	m1.setFecha("");
	m1.setColor("");

	cout << m1.getDatos() << endl << endl;
	
	cout << m1.getId() << endl;
	m1.setId(2);
	cout << m1.getId() << endl;
	m1.setId(-4);
	cout << m1.getId() << endl;

	Mesa m2(2222), m3(3333), m4(4444);

	cout << m2.getDatos() << endl << endl;

	Pedido miPedido;

	miPedido.addPedido(m2);
	miPedido.addPedido(m3);
	cout << miPedido.size() << endl;

	miPedido.deletePedido(m2.getModelo());
	miPedido.deletePedido(m3);
	cout << miPedido.size() << endl;

	miPedido.addPedido(m2);
	miPedido.addPedido(m3);	
	miPedido.addPedido(m4);	
	miPedido.write();

	return 0;
}