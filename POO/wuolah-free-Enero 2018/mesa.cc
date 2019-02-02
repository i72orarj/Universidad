// mesa.cc
// Cuerpo de la clase mesa
#include "mueble.h"
#include "mesa.h"

Mesa::Mesa(int id) : Mueble(id) {
	setNombre("mesa");
	setPatas(0);
	setMaterial("NO_ASIGNADO");
}

bool Mesa::checkEstado() const {
	if(getId()==0 or getPatas()==0 or getNombre()=="NO_ASIGNADO" or 
		getModelo()=="NO_ASIGNADO" or getFecha()=="NO_ASIGNADO" or 
		getColor()=="NO_ASIGNADO")
		return false;
	else return true;
}