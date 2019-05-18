#ifndef __ALGORITMOSGRAFOS_H__
#define __ALGORITMOSGRAFOS_H__
#include <iostream>

#include "grafo.hpp"
using namespace ed;
using namespace std;

template <class G_Nodo, class G_Lado>
class AlgoritmosGrafos
{
public:

  G_Nodo** algoritmoFloyd(Grafo<G_Nodo, G_Lado> &g){
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
    std::cout << "\n******************  Matriz de distancias minimas  *********************\n" << '\n';
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
    std::cout << "\n*******************  Matriz de caminos  *******************************\n" << '\n';
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
    std::cout << "\n***********************************************************************\n" << '\n';
    return matrizCamino;
  }

  void recorridos(Grafo<G_Nodo,G_Lado> &g,G_Nodo** &matrizCamino, const G_Nodo &p1, const G_Nodo &p2){
    G_Nodo provincia_aux;
    int n1=posicion(g,p1), n2=posicion(g,p2);
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
  }

  int posicion(Grafo<G_Nodo,G_Lado> &g,const G_Nodo &s){
     for(int i=0;i<g.getDimension();i++){
       if(g.getNodos()[i]==s){
         return i;
       }
     }
     return -1;
   }

};

#endif
