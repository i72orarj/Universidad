#include "funciones.h"

int main(int argc, char const *argv[]) {
  int num;
  printf("Introduce un numero\n" );
  scanf("%d",&num);
  int sum=sumaDigitos(num);
  printf("La suma de sus digitos es: %d\n",sum );
  return 0;
}
