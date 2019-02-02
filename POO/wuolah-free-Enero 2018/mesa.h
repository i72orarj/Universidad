// mesa.h
// Cabecera de la clase mesa
#ifndef MESA_H
#define MESA_H

#include <string>

#include "mueble.h"

using namespace std;

class Mesa: public Mueble {
private:
	int patas_;
	string material_;
public:
	Mesa(int id);

	inline int getPatas() const {return patas_;}
	inline void setPatas(int patas) {patas_=patas;}

	inline string getMaterial() const {return material_;}
	inline void setMaterial(string material) {material_=material;}

	bool checkEstado() const;

};

#endif