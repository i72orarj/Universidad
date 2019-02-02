#include "ruleta.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>

int Ruleta::foundJugador(Jugador j){
  list<Jugador>::iterator ptr;
  //Jugador aux;
  ptr=jugadores_.begin();
  while(ptr!=jugadores_.end()){
    //aux=*ptr;
    if(ptr->getDNI()==j.getDNI())return 1;
    ptr++;
  }
  return 0;
}
bool Ruleta::addJugador(Jugador j){
  int found=foundJugador(j);
  if(found==0){
    jugadores_.push_back(j);
    std::string nFichero=j.getDNI()+".txt";
    ifstream fichero(nFichero.c_str());
    if(fichero.is_open()){
      fichero.close();
      return true;
    }
    ofstream fichero2(nFichero.c_str());
    fichero.close();
    return true;
  }
  else{
    return false;
  }
}
/*Ruleta::Ruleta int deleteJugador(string dni){
  Jugador aux;
  aux.setDNI(dni);
  inf found=foundJugador(aux);
  if(found==0){
    return -2;
  }
  if(found==1){
    jugadores_.remove(aux);
    return 1;
  }
}*/
int Ruleta::deleteJugador(Jugador j){
  if(jugadores_.empty()==true)return -1;
  int found=foundJugador(j);
  if(found==0){
    return -2;
  }
  if(found==1){
    list <Jugador>::iterator i;
    for(i=jugadores_.begin();i!=jugadores_.end();i++){
      if(i->getDNI()==j.getDNI()){
        jugadores_.erase(i);
        return 1;
      }
    }
  }
}
void Ruleta::escribeJugadores(){
  fstream fichero;
  fichero.open("jugadores.txt",ios::out);
  //Jugador aux;
  list <Jugador>::iterator ptr;
  ptr=jugadores_.begin();
  while(ptr!=jugadores_.end()){
    //aux=*ptr;
    fichero<<ptr->getDNI()<<","<<ptr->getCodigo()<<","<<ptr->getNombre()<<","<<ptr->getApellidos()<<","<<ptr->getEdad()<<","<<ptr->getDireccion()<<","<<ptr->getLocalidad()<<","<<ptr->getProvincia()<<","<<ptr->getPais()<<","<<ptr->getDinero()<<'\n';
    ptr++;
  }
  fichero.close();
}
void Ruleta::leeJugadores(){
  jugadores_.clear();
  Jugador aux("","");
  char cad[30];
  ifstream fichero;
  fichero.open("jugadores.txt");
  while((fichero.getline(cad,30,','))&& (!fichero.eof())){
    aux.setDNI(cad);
    fichero.getline(cad,30,',');
    aux.setCodigo(cad);
    fichero.getline(cad,30,',');
    aux.setNombre(cad);
    fichero.getline(cad,30,',');
    aux.setApellidos(cad);
    fichero.getline(cad,30,',');
    int edad=atoi(cad);
    aux.setEdad(edad);
    fichero.getline(cad,30,',');
    aux.setDireccion(cad);
    fichero.getline(cad,30,',');
    aux.setLocalidad(cad);
    fichero.getline(cad,30,',');
    aux.setProvincia(cad);
    fichero.getline(cad,30,',');
    aux.setPais(cad);
    fichero.getline(cad,30,'\n');
    int dinero=atoi(cad);
    aux.setDinero(dinero);
    jugadores_.push_back(aux);
  }
  fichero.close();
}

void Ruleta::getPremios(){

	list <Apuesta>::iterator iap;
	list <Jugador>::iterator ijug;
	list <Apuesta> aux;

	for(ijug=jugadores_.begin(); ijug!=jugadores_.end(); ijug++){
		//se cargan las apuestas del jugador ijug en la lista aux de apuestas
		ijug->setApuestas();
		aux=ijug->getApuestas();

		//se recorren estas apuestas y se tratan para hacer el reparto de ganancias/perdidas.
		for(iap=aux.begin(); iap!=aux.end();iap++)
			tratarApuestas(*ijug,*iap);
	}
}

void Ruleta::tratarApuestas(Jugador &j,Apuesta a){

	int opcion=a.tipo;

	switch (opcion){

		case 1: if(atoi(a.valor.c_str())==getBola()){//Si aciertas el numero ganas el 36.00 de lo que apuestas

			j.setDinero((j.getDinero()+(35*a.cantidad)));
			setBanca((getBanca()-35*a.cantidad));
		}
			else{ //y si pierdes pierdes lo apostado y lo gana la banca
				j.setDinero((j.getDinero()-a.cantidad));
				setBanca((getBanca()+a.cantidad));
			}
		break;

		case 2:	if(getBola()==0){ //si sale el cero lo pierdes todo lo que hayas apostado

			j.setDinero(j.getDinero()-a.cantidad);
			setBanca(getBanca()+a.cantidad);
		}
			else{ //pero si no sale y aciertas color ganas 2.0 de lo que apuestes
				if((a.valor=="negro" && ((getBola()%2 + ((getBola()/10)%2))%2)==1 )||(a.valor=="rojo"  && ((getBola()%2 + ((getBola()/10)%2))%2)==0)){

					j.setDinero(j.getDinero()+a.cantidad);
					setBanca(getBanca()-a.cantidad);
				}

				else{ //y si no aciertas color pierdes lo apostado

					j.setDinero(j.getDinero()-a.cantidad);
					setBanca(getBanca()+a.cantidad);
				}
			}
		break;

		case 3:	if(getBola()==0){//si la bola sale cero pierdes lo apostado

			j.setDinero(j.getDinero()-a.cantidad);
			setBanca(getBanca()+a.cantidad);
		}

				else{ //y si no sale cero y aciertas par/impar ganas 2.0 y la banca lo pierde
					if((a.valor=="par" && getBola()%2==0) || (a.valor =="impar" && getBola()%2==1)){

					j.setDinero(j.getDinero()+a.cantidad);
					setBanca(getBanca()-a.cantidad);
					}
					else{//y si no aciertas pierdes lo apostado

						j.setDinero(j.getDinero()-a.cantidad);
						setBanca(getBanca()+a.cantidad);
					}
				}
		break;


		case 4: if(getBola()==0){//si la bola sale 0 pierdes lo apostado

			j.setDinero(j.getDinero()-a.cantidad);
			setBanca(getBanca()+a.cantidad);
		}
		else{//y si no y aciertas si es bajo o alto ganas 2.0 de tus apuestas
			if((a.valor=="bajo" && (getBola()>=1 && getBola()<=18)) || ((a.valor=="alto" && (getBola()>=19 && getBola()<=36)))){

			j.setDinero(j.getDinero()+a.cantidad);
			setBanca(getBanca()-a.cantidad);

			}
			else{//pero si no aciertas pierdes lo apostado y lo gana la banca

				j.setDinero(j.getDinero()-a.cantidad);
				setBanca(getBanca()+a.cantidad);
			}
		}
	break;

	default: cout<< "Error en la apuesta";
	exit(-1);
	}
}


/*
void Ruleta::getPremios(){
  list<Jugador>::iterator ijug;
  list<Apuesta>::iterator iap;
  list<Apuesta> aux;

  for(ijug=jugadores_.begin();ijug!=jugadores_.end();ijug++){
    ijug->setApuestas();
    aux=ijug->getApuestas();
  }
  for(iap=aux.begin();iap!=aux.end();iap++){
    tratarApuestas(*ijug,*iap);
  }
}

void Ruleta::tratarApuestas(Jugador &j,Apuesta a){
  int opcion=a.tipo;
  switch (opcion) {
    case 1:
    if (atoi(a.valor.c_str())==getBola()){
      j.setDinero(j.getDinero()+(35*a.cantidad));
      setBanca((getBanca()-35*a.cantidad));
    }
    else{
      j.setDinero(j.getDinero()-a.cantidad);
      setBanca(getBanca()+a.cantidad);
    }
    break;
    case 2:
    if(getBola()==0){
      j.setDinero(j.getDinero()-a.cantidad);
      setBanca(getBanca()+a.cantidad);
    }
    else{
      if(((a.valor=="negro" && ((getBola()%2 + ((getBola()/10)%2))%2)==1 )||(a.valor=="rojo"  && ((getBola()%2 + ((getBola()/10)%2))%2)==0))){
        j.setDinero(j.getDinero()+a.cantidad);
        setBanca(getBanca()-a.cantidad);
      }
      else{
        j.setDinero(j.getDinero()-a.cantidad);
        setBanca(getBanca()+a.cantidad);
      }
    }
    break;
    case 3:
    if(getBola()==0){
      j.setDinero(j.getDinero()-a.cantidad);
      setBanca(getBanca()+a.cantidad);
    }
    else{
      if((a.valor=="par" && getBola()%2==0) || (a.valor =="impar" && getBola()%2==1)){
        j.setDinero(j.getDinero()+a.cantidad);
        setBanca(getBanca()-a.cantidad);
      }
      else{
        j.setDinero(j.getDinero()-a.cantidad);
        setBanca(getBanca()+a.cantidad);
      }
    }
    break;
    case 4:
    if(getBola()==0){
      j.setDinero(j.getDinero()-a.cantidad);
      setBanca(getBanca()+a.cantidad);
    }
    else{
      if((a.valor=="bajo" && (getBola()>=1 && getBola()<=18)) || ((a.valor=="alto" && (getBola()>=19 && getBola()<=36)))){
        j.setDinero(j.getDinero()+a.cantidad);
        setBanca(getBanca()-a.cantidad);
      }
      else{
        j.setDinero(j.getDinero()-a.cantidad);
        setBanca(getBanca()+a.cantidad);
      }
    }
    break;
    default: std::cout << "Error en la apuesta" << '\n';
    exit(-1);
  }
}
*/
