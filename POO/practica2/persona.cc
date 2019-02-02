#include "persona.h"

using namespace std;

bool Persona::mayor(){
  if(edad_>=18){
    return true;
  }
  else{
    return false;
  }
}
/*Persona::Persona(string dni){
  setDNI(dni);
  nombre_="";
  apellidos_="";
  edad_=0;
  direccion_="";
  localidad_="";
  provincia_="";
  pais_="";
}
Persona::Persona(string dni,string nombre="",string apellidos="",int edad=0,string direccion="",string localidad="",string provincia="",string pais=""){
  setDNI(dni);
  setNombre(nombre);
  setApellidos(apellidos);
  setEdad(edad);
  setDireccion(direccion);
  setLocalidad(localidad);
  setProvincia(provincia);
  setPais(pais);
}*/
