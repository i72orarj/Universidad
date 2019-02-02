#include "dados.h"
#include <iostream>

int main(int argc, char const *argv[]) {
  int d1,d2,opcion=7;
  int v1[5],v2[5];
  Dados d;
  Dados();
  while(opcion!=0){
  //  std::cout << "Que desea hacer?" << '\n';
    std::cout << "#########################################" << '\n';
    std::cout << "1.- Lanzar dados" << '\n';
    std::cout << "2.- Conocer el valor del dado 1" << '\n';
    std::cout << "3.- Conocer el valor del dado 2" << '\n';
    std::cout << "4.- Seleccionar un valor para el dado 1" << '\n';
    std::cout << "5.- Seleccionar un valor para el dado 2" << '\n';
    std::cout << "6.- Suma de los dos dados" << '\n';
    std::cout << "7.- Media de los valores del dado 1" << '\n';
    std::cout << "8.- Media de los valores del dado 2" << '\n';
    std::cout << "9.- Numero de lanzamientos del dado 1" << '\n';
    std::cout << "10.- Numero de lanzamientos del dado 2" << '\n';
    std::cout << "11.- Ultimos 5 valores del dado 1" << '\n';
    std::cout << "12.- Ultimos 5 valores del dado 2" << '\n';
    std::cout << "0.- Salir" << '\n';
    std::cout << "#########################################" << '\n';
    std::cout << "Opcion: " ;
    std::cin >> opcion;
    switch (opcion) {
      case 1:
        d.lanzamiento();
        std::cout << "Dados lanzados" << '\n';
      break;
      case 2:
        std::cout << "Dado 1 = " <<d.getDado1()<< '\n';
      break;
      case 3:
        std::cout << "Dado 2 = " <<d.getDado2()<< '\n';
      break;
      case 4:
        std::cout << "Valor para el dado 1: ";
        std::cin >> d1;
        if(d.setDado1(d1)!=true){
          std::cout << "Valor imposible para el dado" << '\n';
        }
        else{
          std::cout << "Valor fijado" << '\n';
        }
      break;
      case 5:
        std::cout << "Valor para el dado 2: ";
        std::cin >> d2;
        if(d.setDado1(d2)!=true){
          std::cout << "Valor imposible para el dado" << '\n';
        }
        else{
          std::cout << "Valor fijado" << '\n';
        }
      break;
      case 6:
        std::cout << "La suma es: " <<d.getSuma() <<'\n';
      break;
      case 7:
        std::cout << "La media de los valores del dado 1 es: " <<d.getMedia1()<< '\n';
      break;
      case 8:
        std::cout << "La media de los valores del dado 2 es: " <<d.getMedia2()<< '\n';
      break;
      case 9:
        if(d.getLanzamientos1()==1){
          std::cout << "1 lanzamiento" << '\n';
        }
        else{
          std::cout << d.getLanzamientos1()<< " lanzamientos" << '\n';
        }
      break;
      case 10:
        if(d.getLanzamientos2()==1){
          std::cout << "1 lanzamiento" << '\n';
        }
        else{
          std::cout << d.getLanzamientos2()<< " lanzamientos" << '\n';
        }
      break;
      case 11:
        d.getUltimos1(v1);
        for(int i=0;(i<5)&&(v1[i]!=0);i++){
          std::cout << v1[i] << '\t';
        }
        std::cout  << '\n';
      break;
      case 12:
        d.getUltimos2(v2);
        for(int i=0;(i<5)&&(v2[i]!=0);i++){
          std::cout << v2[i] << '\t';
        }
        std::cout << '\n';
      break;

    }
  }
  return 0;
}
