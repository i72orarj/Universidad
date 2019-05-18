#ifndef __FUNCIONES_HPP
#define __FUNCIONES_HPP

#include <iostream>
#include <cstring>
#include <cstdlib> //Para usar system
#include <fstream> //Para trabajar con ficheros

#include "grafo.hpp"
#include "algoritmosgrafos.hpp"


using namespace std;
using namespace ed;

int menu()
{
  int opcion;

  system("clear");
  cout << "  0. Salir................................\n";
  cout << "  1. Cargar grafo desde fichero...........\n";
  cout << "  2. Algoritmo de Floyd (GD y GND)......\n";
  std::cout << "  3. Distancia minima y camino entre dos ciudades......" << '\n';

  cout << "Introduzca opcion...:";
  cin >> opcion;

  return opcion;
}

template <class G_Nodo, class G_Lado>
bool cargarGrafo(Grafo<G_Nodo, G_Lado> &g)//puede no ser puntero?? , siendo puntero setNodos no funciona
{
  string ficheroMatriz="matrizAndalucia.txt", ficheroEtiquetas="Andalucia.txt";

  /*
  cout << "Fichero de la matriz de conexion: ";
  cin >> ficheroMatriz;

  cout << "Fichero de las etiquetas: ";
  cin >> ficheroEtiquetas;
  */
  std::cout << "Estamos trabajando con " <<ficheroMatriz<< " para leer la matriz y con "<<ficheroEtiquetas<< " para leer las etiquetas"<< '\n';
  std::ifstream etiquetas(ficheroEtiquetas.c_str());
  std::ifstream matriz(ficheroMatriz.c_str());
  if(!etiquetas.is_open()){
    std::cout << "No se ha podido abrir el fichero de las etiquetas" << '\n';
    return false;
  }
  else if(!matriz.is_open()){
    std::cout << "No se ha podido abrir el fichero de la matriz de conexion" << '\n';
    return false;
  }
  else{
    G_Nodo nodo;
    G_Lado lado;
    int nEtiquetas=0;
    while(!etiquetas.eof() && etiquetas>>nodo){//saber numero de etiquetas
      nEtiquetas++;
    }
    g.setDimension(nEtiquetas);
    etiquetas.close();
    etiquetas.open(ficheroEtiquetas.c_str());
    // etiquetas.seekg(0,etiquetas.beg);
    G_Nodo* nodos=new G_Nodo[g.getDimension()];
    G_Lado** lados=new G_Lado*[g.getDimension()];
    for(int i=0;i<g.getDimension();i++){
      lados[i]=new G_Lado[g.getDimension()];
    }
    int i=0;
    while(!etiquetas.eof() && etiquetas>>nodo){//leyendo del fichero y pasando al vector auxiliar
      nodos[i]=nodo;
      i++;
    }
    g.setNodos(nodos);
    for(int fila=0;fila<g.getDimension();fila++){//leyendo del fichero y pasando a matriz auxiliar
      for(int columna=0;columna<g.getDimension();columna++){
        if(!matriz.eof() && matriz>>lado){
          lados[fila][columna]=lado;
        }
      }
    }
    g.setLados(lados);
  }
  etiquetas.close();
  matriz.close();
  return true;
}
/*
template <class G_Nodo, class G_Lado>
G_Nodo** algoritmoFloyd( Grafo<G_Nodo, G_Lado> &g)
{
  std::cout << "***********************************************************************" << '\n';
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
  G_Lado** lados=g.getLados();//matriz auxiliar para trabajar con las distancias
  int n=g.getDimension();
  G_Nodo** matrizCamino=new G_Nodo*[n];
  for(int i=0;i<n;i++){
    matrizCamino[i]=new G_Nodo[n];
  }
  for(int j=0;j<n;j++){//columna de la matriz
    for(int i=0;i<n;i++){//fila de la matriz
      matrizCamino[i][j]=g.getNodos()[j];
    }
  }
  for(int i=0;i<n;i++){
    lados[i][i]=0;
  }
  for(int k=0;k<n;k++){//indica el subindice que se esta evaluando
    for(int i=0;i<n;i++){//fila de la matriz
      for(int j=0;j<n;j++){//columna de la matriz
        if((lados[i][k]+lados[k][j])<lados[i][j]){
          lados[i][j]=(lados[i][k]+lados[k][j]);
          matrizCamino[i][j]=g.getNodos()[k];
        }
      }
    }
  }
  //g.setLados(lados);
  std::cout << "***********************************************************************" << '\n';
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
  std::cout << "***********************************************************************" << '\n';
  return matrizCamino;
}

 template <class G_Nodo, class G_Lado>
 void recorridos(Grafo<G_Nodo,G_Lado> &g,G_Nodo** matrizCamino, G_Nodo &p1, G_Nodo &p2){
  G_Nodo provincia_aux;
  int n1=posicion(g,p1), n2=posicion(g,p2), aux_int;
  G_Lado distancia=g.getLados()[n1][n2];
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

template <class G_Nodo, class G_Lado>
int posicion(Grafo<G_Nodo,G_Lado> &g,G_Nodo &s);//{
  for(int i=0;i<g.getDimension();i++){
    if(g.getNodos()[i]==s){
      return i;
    }
  }
  return -1;
}*/
#endif
