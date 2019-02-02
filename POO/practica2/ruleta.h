#ifndef RULETA_H
#define RULETA_H

#include <list>
#include <cstdlib>
#include "crupier.h"
#include "jugador.h"

using namespace std;

class Ruleta {
private:
int banca_;
int bola_;
Crupier crupier_;
list <Jugador> jugadores_;
public:
Ruleta(Crupier c):crupier_(c){
  srand(time(NULL));
  bola_=-1;
  banca_=1000000;
  // Crupier(string dni,string codigo,string nombre="",string apellidos="",int edad=0,string direccion="",string localidad="",string provincia="",string pais=""):Persona(dni,nombre,apellidos,edad,direccion,localidad,provincia,pais)
}
int foundJugador(Jugador j);
inline int getBanca(){return banca_;};
inline bool setBanca(int banca){
  if(banca>=0){
    banca_=banca;
    return true;
  }
  else{return false;}
}
inline int getBola(){return bola_;};
inline bool setBola(int bola){
  if((bola>=0)&&(bola<=36)){
    bola_=bola;
    return true;
  }
  else{return false;}
}
inline Crupier getCrupier(){return crupier_;};
inline void setCrupier(Crupier crupier){crupier_=crupier;}
inline list <Jugador> getJugadores(){return jugadores_;};
bool addJugador(Jugador j);
int deleteJugador(Jugador j);
void escribeJugadores();
void leeJugadores();
inline void giraRuleta(){setBola(rand()%37);};
void getPremios();
void tratarApuestas(Jugador &j,Apuesta a);
};
#endif
