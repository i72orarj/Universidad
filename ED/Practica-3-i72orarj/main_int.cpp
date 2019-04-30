#include <iostream>
#include <cstdlib> //para usar srand()
#include "arbolbinarioordenadoenlazado.hpp"
#include "operadornodo.hpp"
#include "persona.hpp"
#include "generarpersona.hpp"

using namespace ed;

int menu();
void insertarPersonas(ed::ArbolBinarioOrdenadoEnlazado<int> &a);
void buscarPersona(ed::ArbolBinarioOrdenadoEnlazado<int> &a);
void imprimirArbol(ed::ArbolBinarioOrdenadoEnlazado<int> &a);
void borrarPersona(ed::ArbolBinarioOrdenadoEnlazado<int> &a);

int main()
{
  srand(time(0));
  ArbolBinarioOrdenadoEnlazado<int> a;
  int opcion=-1;
  while(opcion!=0){
    opcion=menu();
    switch (opcion) {
      case 1:
        insertarPersonas(a);
      break;
      case 2:
        buscarPersona(a);
      break;
      case 3:
        imprimirArbol(a);
      break;
      case 4:
        borrarPersona(a);
      break;
      case 5:
        a.borrarArbol();
        opcion=0;
      break;
      case 0:
        std::cout << "Saliendo del programa" << '\n';
      break;
      default:
        std::cout << "Selecciona una opcion valida" << '\n';
      break;
    }
  }
}

int menu(){
  int opcion=-1;
  std::cout << "Menú Principal" << endl;
  std::cout << "\t1: Escribe un número de enteros en el árbol" << endl;
  std::cout << "\t2: Comprueba si un entero, dado su valor, existe en el árbol" << endl;
  std::cout << "\t3: Imprime el árbol usando los 3 tipos de recorridos" << endl;
  std::cout << "\t4: Borra a un entero, dado su valor" << endl;
  std::cout << "\t5: Borra el árbol" << endl;
  std::cout << "Introduzca una opcion: ";
  std::cin >> opcion;
  return opcion;
}
void insertarPersonas(ed::ArbolBinarioOrdenadoEnlazado<int> &a){
  int nEnteros=12;
  int n;
  for(int i=0;i<nEnteros;i++){
    std::cout << "Introduzca valor: " ;
    std::cin >> n;
    a.insertar(n);
  }
}
void imprimirArbol(ed::ArbolBinarioOrdenadoEnlazado<int> &a){
  EscribirNodo<int> operador;
  std::cout << "---------RECORRIDO PREORDEN------" << '\n';
  a.recorridoPreOrden(operador);
  std::cout  << '\n';
  std::cout << "---------RECORRIDO INORDEN-------" << '\n';
  a.recorridoInOrden(operador);
  std::cout  << '\n';
  std::cout << "---------RECORRIDO POSTORDEN-----" << '\n';
  a.recorridoPostOrden(operador);
  std::cout  << '\n';
}
void buscarPersona(ed::ArbolBinarioOrdenadoEnlazado<int> &a){
  int n;
  std::cout << "Introduzca valor" << '\n';
  std::cin >> n;
  if(a.buscar(n)){
    std::cout << "entero encontrado en el arbol" << '\n'<<'\n';
  }
  else{
    std::cout << "Entero no encontrado en el arbol" << '\n'<<'\n';
  }
}
void borrarPersona(ed::ArbolBinarioOrdenadoEnlazado<int> &a){
  int n;
  std::cout << "Introduzca valor" << '\n';
  std::cin >> n;
  if(a.buscar(n)){
    std::cout << "Entero encontrado en el arbol, se va a proceder al borrado" << '\n';
    if(a.borrar()){
      std::cout << "Entero borrado satisfactoriamente" << '\n';
    }
    else{
      std::cout << "No se ha podido borrar a el entero del arbol" << '\n'<<'\n';
    }
  }
  else{
    std::cout << "Entero no encontrado en el arbol" << '\n'<<'\n';
  }
}
