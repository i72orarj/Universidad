#include "jugador.h"
#include "persona.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace std;

void Jugador::setApuestas(){
  Apuesta a;
  char tipo[30],valor[30],cantidad[30];
  string nFichero=getDNI()+".txt";
  apuestas_.clear();
  ifstream fichero(nFichero.c_str());
  if(fichero.is_open()){
    while(fichero.getline(tipo,30,',')){
      fichero.getline(valor,30,',');
      fichero.getline(cantidad,30,'\n');
      a.tipo=atoi(tipo);
      a.valor=valor;
      a.cantidad=atoi(cantidad);
      apuestas_.push_back(a);
    }
  }
  else{
    std::cout << "Error al abrir el fichero" << '\n';
  }
  fichero.close();
}
/*Jugador::Jugador(string dni,string codigo){
  codigo_=codigo;
  setDinero(1000);
  Persona(string dni);
}
Jugador::Jugador(string dni,string codigo,string nombre="",string apellidos="",int edad=0,string direccion="",string localidad="",string provincia="",string pais=""):Persona(dni,nombre,apellidos,edad,direccion,localidad,provincia,pais){
  setCodigo(codigo);
  setDinero(1000);
  //Persona(string dni,string nombre,string apellidos,int edad,string direccion,string localidad,string provincia,string pais);
}*/
