#ifndef PERSONA_H
#define  PERSONA_H

#include <string>

using namespace std;

class Persona {
private:
  string dni_;
  string nombre_;
  string apellidos_;
  int edad_;
  string direccion_;
  string localidad_;
  string provincia_;
  string pais_;
public:
  inline void setDNI(string s){dni_=s;};
  inline string getDNI(){return dni_;};
  inline void setNombre(string s){nombre_=s;};
  inline string getNombre(){return nombre_;};
  inline void setApellidos(string s){apellidos_=s;};
  inline string getApellidos(){return apellidos_;};
  inline void setEdad(int s){edad_=s;};
  inline int getEdad(){return edad_;};
  inline void setDireccion(string s){direccion_=s;};
  inline string getDireccion(){return direccion_;};
  inline void setLocalidad(string s){localidad_=s;};
  inline string getLocalidad(){return localidad_;};
  inline void setProvincia(string s){provincia_=s;};
  inline string getProvincia(){return provincia_;};
  inline void setPais(string s){pais_=s;};
  inline string getPais(){return pais_;};
  inline string getApellidosyNombre(){return apellidos_+", "+nombre_;};
  bool mayor();
  //Persona(string dni);
  //Persona(string dni,string nombre,string apellidos,int edad,string direccion,string localidad,string provincia,string pais);
  Persona(string dni,string nombre="",string apellidos="",int edad=0,string direccion="",string localidad="",string provincia="",string pais=""){
    dni_=dni; nombre_=nombre;apellidos_=apellidos;edad_=edad;direccion_=direccion;localidad_=localidad;provincia_=provincia; pais_=pais;}
};
#endif
