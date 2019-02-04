#include "funciones.h"

int sumaDigitos(int num){
  if(num<10){
    return num;
  }
  else{
    return(num%10+sumaDigitos(num/10));
  }
}
