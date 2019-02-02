#ifndef CRUPIER_H
#define CRUPIER_H

#include <string>
#include "persona.h"

using namespace std;

class Crupier:public Persona {
private:
  string codigo_;
public:
  inline void setCodigo(string s){codigo_=s;};
  inline string getCodigo(){return codigo_;};
  //Crupier(string dni,string codigo);
  //Crupier(string dni,string codigo,string nombre,string apellidos,int edad,string direccion,string localidad,string provincia,string pais);
  Crupier(string dni,string codigo,string nombre="",string apellidos="",int edad=0,string direccion="",string localidad="",string provincia="",string pais=""):Persona(dni,nombre,apellidos,edad,direccion,localidad,provincia,pais){codigo_=codigo;};
};

#endif
