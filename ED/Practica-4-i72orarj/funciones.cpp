#include "grafo.hpp"
#include <iostream>
#include "funciones.hpp"
#include <string>

using namespace ed;

// template <class G_Nodo, class G_Lado>
// void recorridos(Grafo<G_Nodo,G_Lado> &g,G_Nodo** matrizCamino, G_Nodo &p1, G_Nodo &p2){
//   G_Nodo provincia_aux;
//   int n1=posicion(g,p1), n2=posicion(g,p2), aux_int;
//   G_Lado distancia=g.getLados()[n1][n2];
//   std::cout << "Recorrido desde " <<p1<<" hasta " <<p2<<'\n';
//   std::cout << p1 <<" -> ";
//   provincia_aux=matrizCamino[n1][n2];;
//   std::cout << provincia_aux;
//   while(posicion(g,provincia_aux)!=n2){
//     n1=posicion(g,provincia_aux);
//     provincia_aux=matrizCamino[n1][n2];
//     std::cout << " -> " <<provincia_aux;
//   }
//
//   // std::cout <<" -> "<<p2<< '\n';
//   std::cout << '\n';
//   std::cout << "Distancia: " <<distancia<< '\n';
//   return;
// }

template <class G_Nodo, class G_Lado>
int posicion(Grafo<G_Nodo,G_Lado> &g,G_Nodo &s){
  for(int i=0;i<g.getDimension();i++){
    if(g.getNodos()[i]==s){
      return i;
    }
  }
  return -1;
}
