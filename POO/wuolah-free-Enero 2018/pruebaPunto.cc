// prueba.cc
// Programa principal que prueba la funcionalidad de 
// la clase punto.

// g++ pruebaPunto.cc punto.cc -Wall

#include <iostream>

#include "punto.h"

using namespace std;

int main(int argc, char const *argv[]) {
	Punto p1(4,2);
	cout << p1.getX() << "," << p1.getY() << endl;

	Punto p2(0,0);
	p2.setX(3);
	p2.setY(6);
	cout << p2.getX() << "," << p2.getY() << endl;

	p2=p1;
	cout << p2.getX() << "," << p2.getY() << endl;

	p2++;
	cout << p2.getX() << "," << p2.getY() << endl;

	p1=p2++;
	cout << p1.getX() << "," << p1.getY() << endl;
	cout << p2.getX() << "," << p2.getY() << endl;

	p1=p1+1;
	cout << p1.getX() << "," << p1.getY() << endl;

	Punto p3=p2+2;
	cout << p3.getX() << "," << p3.getY() << endl;

	p2=2+p2;
	cout << p3.getX() << "," << p3.getY() << endl;
	
	return 0;
}
