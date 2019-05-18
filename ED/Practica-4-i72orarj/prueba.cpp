#include <iostream>
#include <cstring>
// #include <cstdlib> //Para usar system
// #include <fstream> //Para trabajar con ficheros

#include "grafo.hpp"
// #include "algoritmosgrafos.hpp"
#include "funciones.hpp"

void recorridos(Grafo<std::string,int> &g,std::string** matrizCamino, std::string &p1, std::string &p2);

int posicion(Grafo<std::string,int> &g,std::string &s);

int main(int argc, char const *argv[]) {
  Grafo<std::string,int> g;
  cargarGrafo(g);
  std::cout  << '\t';//imprime matriz cargada de los ficheros
  for(int i=0;i<g.getDimension();i++){
    std::cout << g.getNodos()[i] << '\t';
  }
  std::cout  << '\n';
  for(int fila=0;fila<g.getDimension();fila++){
    std::cout << g.getNodos()[fila] << '\t';
    for(int columna=0;columna<g.getDimension();columna++){
      std::cout << g.getLados()[fila][columna] << '\t';
    }
    std::cout  << '\n';
  }
  std::cout << "***********************************************************************" << '\n';
  std::string** matrizCamino=algoritmoFloyd(g);
  std::cout  << '\t';//imprime matriz de distancias minimas
  for(int i=0;i<g.getDimension();i++){
    std::cout << g.getNodos()[i] << '\t';
  }
  std::cout  << '\n';
  for(int fila=0;fila<g.getDimension();fila++){
    std::cout << g.getNodos()[fila] << '\t';
    for(int columna=0;columna<g.getDimension();columna++){
      std::cout << g.getLados()[fila][columna] << '\t';
    }
    std::cout  << '\n';
  }
  std::cout << "***********************************************************************" << '\n';
  std::cout  << '\t';//imprime matriz de camino
  for(int i=0;i<g.getDimension();i++){
    std::cout << g.getNodos()[i] << '\t';
  }
  std::cout  << '\n';
  for(int fila=0;fila<g.getDimension();fila++){
    std::cout << g.getNodos()[fila] << '\t';
    for(int columna=0;columna<g.getDimension();columna++){
      std::cout << matrizCamino[fila][columna] << '\t';
    }
    std::cout  << '\n';
  }
  std::string p1,p2;
  std::cout << "Introduzca dos provincias: ";
  std::cin >> p1;
  std::cin >> p2;
  recorridos(g,matrizCamino,p1,p2);
  return 0;
}

void recorridos(Grafo<std::string,int> &g,std::string** matrizCamino, std::string &p1, std::string &p2){
  std::string provincia_aux;
  int n1=posicion(g,p1), n2=posicion(g,p2), aux_int;
  int distancia=g.getLados()[n1][n2];
  std::cout << "Recorrido desde " <<p1<<" hasta " <<p2<<'\n';
  std::cout << p1 <<" -> ";
  provincia_aux=matrizCamino[n1][n2];;
  std::cout << provincia_aux;
  while(posicion(g,provincia_aux)!=n2){
    n1=posicion(g,provincia_aux);
    provincia_aux=matrizCamino[n1][n2];
    std::cout << " -> " <<provincia_aux;
  }

  // std::cout <<" -> "<<p2<< '\n';
  std::cout << '\n';
  std::cout << "Distancia: " <<distancia<< '\n';
  return;
}

int posicion(Grafo<std::string,int> &g,std::string &s){
  for(int i=0;i<g.getDimension();i++){
    if(g.getNodos()[i]==s){
      return i;
    }
  }
  return -1;
}
