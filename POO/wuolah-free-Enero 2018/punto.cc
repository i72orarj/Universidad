// punto.cc
// Cuerpo de la clase punto

#include "punto.h"

Punto& Punto::operator=(const Punto &p) { // const necesario
	//this->x_ = p.getX();
	//this->y_ = p.getY();
	x_ = p.getX();
	y_ = p.getY();
	return *this; 
}

Punto& Punto::operator++(void) { // prefijo ++p
	//this->x_++;
	//this->y_++;
	x_++;
	y_++;
	return *this;
} 

Punto Punto::operator++(int) { // postfijo p++
	Punto temp=*this;
	//this->x_++;
	//this->y_++;
	x_++;
	y_++;
	return temp;
}

Punto Punto::operator+(int a) {
	Punto aux=*this;
	aux.x_ = aux.getX() + a;
	aux.y_ = aux.getY() + a;
	return aux;
}

Punto operator+(int a, Punto p) {
	Punto aux=p;
	aux.setX(aux.getX() + a);
	aux.setY(aux.getY() + a);
	return aux;
}