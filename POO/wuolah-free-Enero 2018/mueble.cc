// mueble.cc
// Cuerpo de la clase mueble
#include "mueble.h"

Mueble::Mueble( int id, string nombre, string modelo, string fecha, 
				string color) {
	if(id<0) {
		setId(0);
	} else setId(id);

	setNombre(nombre);
	setModelo(modelo);
	setFecha(fecha);
	setColor(color);
}

bool Mueble::setId(int id) {
	if(id>=0) {
		id_=id;
		return true;
	} else return false;
}

bool Mueble::setNombre(string nombre) {
	if(nombre!="") {
		nombre_=nombre;
		return true;
	} else return false;
}

bool Mueble::setModelo(string modelo) {
	if(modelo!="") {
		modelo_=modelo;
		return true;
	} else return false;	
}

bool Mueble::setFecha(string fecha) {
	if(fecha!="") {
		fecha_=fecha;
		return true;
	} else return false;
}

bool Mueble::setColor(string color) {
	if(color!="") {
		color_=color;
		return true;
	} else return false;
}
