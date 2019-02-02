// mueble.h
// Cabecera de la clase mueble
#ifndef MUEBLE_H
#define MUEBLE_H

#include <string>	// Clase de la C++ Standard Library

using namespace std;	// Para no poner std::string

/*
	TAD: Mueble

	DESCRIPCION:
		El TAD Mueble representa y gestiona los datos de un mueble

	OPERACIONES:

	PROC: Mueble(entero id, string nombre, string modelo, string fecha, 
				 string color) DEV ()
	REQUIERE: True
	MODIFICA: id, nombre, modelo, fecha, color
	EFECTOS: Crea un mueble asignadole los datos "id", "nombre", "modelo", 
	"fecha" y "color" siendo "id" obligatorio y el resto opcionales (tomarían
	el valor "NO_ASIGNADO").

	PROC: getId() DEV (entero)
	REQUIERE: True
	MODIFICA: 0
	EFECTOS: Devuelve el id del mueble (analogo para getNombre(), getModelo(), 
	getFecha() y getColor())

	PROC: setId(entero id) DEV (bool)
	REQUIERE: True
	MODIFICA: Id
	EFECTOS: Asigna "id" como nuevo id del mueble y devuelve verdadero si es 
	mayor o igual que 0. En otro caso devuelve falso.

	PROC: setNombre(string nombre) DEV(bool)
	REQUIERE: True
	MODIFICA: 0
	EFECTOS: Asigna "nombre" como nuevo nombre del mueble y devuelve verdadero
	si no es una cadena vacía "", en este caso devuelve falso (analogo para 
	setModelo(), setFecha() y setColor())

	PROC: getDatos() DEV(string datos)
	REQUIERE: True
	MODIFICA: 0
	EFECTOS: "datos" sera una cadena con la forma: nombre-modelo-fecha-color
	donde cada dato hara referencia a las caracteristicas del mueble.
*/

class Mueble {
private:
	int id_;
	string nombre_, modelo_, fecha_, color_;
public:
	Mueble(int id, string nombre="NO_ASIGNADO", string modelo="NO_ASIGNADO", 
		   string fecha="NO_ASIGNADO", string color="NO_ASIGNADO");
	
	inline int getId() const {return id_;}
	bool setId(int id);

	inline string getNombre() const {return nombre_;}
	bool setNombre(string nombre);

	inline string getModelo() const {return modelo_;}
	bool setModelo(string modelo);

	inline string getFecha() const {return fecha_;}
	bool setFecha(string fecha);

	inline string getColor() const {return color_;}
	bool setColor(string color);

	inline string getDatos() const {
		return (getNombre()+"-"+getModelo()+"-"+getFecha()+"-"+getColor());
	}

};

#endif