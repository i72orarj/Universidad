#include <iostream>
#include <cstdlib> //para usar srand()
#include "arbolbinarioordenadoenlazado.hpp"
#include "operadornodo.hpp"
#include "persona.hpp"
#include "generarpersona.hpp"

using namespace ed;

int menu();
void insertarPersonas(ed::ArbolBinarioOrdenadoEnlazado<Persona> &a);
void buscarPersona(ed::ArbolBinarioOrdenadoEnlazado<Persona> &a);
void imprimirArbol(ed::ArbolBinarioOrdenadoEnlazado<Persona> &a);
void borrarPersona(ed::ArbolBinarioOrdenadoEnlazado<Persona> &a);

int main()
{
  srand(time(0));
  ArbolBinarioOrdenadoEnlazado<Persona> a;
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
      default:
        std::cout << "Selecciona una opcion valida" << '\n';
      break;
    }
    std::cout << "Saliendo del programa" << '\n';
  }
}

int menu(){
  int opcion=-1;
  std::cout << "Menú Principal" << endl;
  std::cout << "\t1: Escribe un número de personas en el árbol" << endl;
  std::cout << "\t2: Comprueba si una persona, dados sus datos, existe en el árbol" << endl;
  std::cout << "\t3: Imprime el árbol usando los 3 tipos de recorridos" << endl;
  std::cout << "\t4: Borra a una persona, dados sus datos" << endl;
  std::cout << "\t5: Borra el árbol" << endl;
  std::cout << "Introduzca una opcion: ";
  std::cin >> opcion;
  return opcion;
}
void insertarPersonas(ed::ArbolBinarioOrdenadoEnlazado<Persona> &a){
  int nPersonas;
  std::cout << "Introduzca el numero de personas que insertara el usuario" << '\n';
  std::cin >> nPersonas;
  while(nPersonas<1){
    std::cout << "Introduzca un numero mayor que 0" << '\n';
    std::cin >> nPersonas;
  }
  for(int i=0;i<nPersonas;i++){
    a.insertar(generarDatosPersonales());
  }
}
void imprimirArbol(ed::ArbolBinarioOrdenadoEnlazado<Persona> &a){
  EscribirNodo<Persona> operador;
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
void buscarPersona(ed::ArbolBinarioOrdenadoEnlazado<Persona> &a){
  Persona p=generarDatosPersonales();
  std::cout << "\nSe buscara a la persona :";
  std::cout << p << '\n';
  if(a.buscar(p)){
    std::cout << "Persona encontrada en el arbol" << '\n'<<'\n';
  }
  else{
    std::cout << "Persona no encontrada en el arbol" << '\n'<<'\n';
  }
}
void borrarPersona(ed::ArbolBinarioOrdenadoEnlazado<Persona> &a){
  Persona p=generarDatosPersonales();
  std::cout << "Se buscara y borrara a la persona ";
  std::cout << p <<'\n';
  if(a.buscar(p)){
    std::cout << "Persona encontrada en el arbol, se va a proceder al borrado" << '\n';
    if(a.borrar()){
      std::cout << "Persona borrada satisfactoriamente" << '\n';
    }
    else{
      std::cout << "No se ha podido borrar a la persona del arbol" << '\n'<<'\n';
    }
  }
  else{
    std::cout << "Persona no encontrada en el arbol" << '\n'<<'\n';
  }
}
