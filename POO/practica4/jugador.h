#ifndef JUGADOR_H
#define JUGADOR_H

#include "persona.h"
#include <string>
#include <list>


using namespace std;

struct Apuesta {
  int tipo;
  string valor;
  int cantidad;
};
class Jugador : public Persona {
private:
  int dinero_;
  string codigo_;
  list <Apuesta> apuestas_;
public:
  inline int getDinero(){return dinero_;};
  inline void setDinero(int dinero){dinero_=dinero;};
  inline string getCodigo(){return codigo_;};
  inline void setCodigo(string s){codigo_=s;};
  inline list <Apuesta> getApuestas(){return apuestas_;};
  void setApuestas();
  //Jugador(string dni,string codigo);
  //Jugador(string dni,string codigo,string nombre,string apellidos,int edad,string direccion,string localidad,string provincia,string pais);
  Jugador(string dni,string codigo,string nombre="",string apellidos="",int edad=0,string direccion="",string localidad="",string provincia="",string pais=""):Persona(dni,nombre,apellidos,edad,direccion,localidad,provincia,pais){
    codigo_=codigo;
    dinero_=1000;
  }
};

#endif
