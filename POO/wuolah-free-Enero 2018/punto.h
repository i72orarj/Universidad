// punto.h
// Cabecera de la clase punto
#ifndef PUNTO_H
#define PUNTO_H

class Punto {
private:
	int x_, y_;
public:
	inline Punto(int x, int y) {x_=x; y_=y;}
	
	inline int getX() const {return x_;}
	inline int getY() const {return y_;}

	inline void setX(int x) {x_=x;}
	inline void setY(int y) {y_=y;}

	Punto& operator=(const Punto &p); // const necesario

	Punto& operator++(void); // prefijo ++p
	Punto operator++(int); // postfijo p++

	Punto operator+(int a);
	friend Punto operator+(int a, Punto p);
};

#endif