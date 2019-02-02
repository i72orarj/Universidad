//guess.cc
//adivinar numero aleatorio

#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, char const *argv[]) {
  int i, aleatorio,encontrado=0;
  srand(time(NULL));
  aleatorio=(rand()%9)+1;
  while(encontrado!=1){
    std::cout << "Introduzca un valor" << '\n';
    std::cin >> i;
    if(i==aleatorio){
      std::cout << "Has adivinado el valor aleatorio" << '\n';
      encontrado=1;
    }
    if(i<aleatorio){
      std::cout << "El valor aleatorio es mayor" << '\n';
    }
    if(i>aleatorio){
      std::cout << "El valor aleatorio es menor" << '\n';
    }
  }
  return 0;
}
