#include "funciones.h"

int main(int argc, char const *argv[]) {
  char nFichero[MAX_STR];
  printf("Fichero a usar:" );
  scanf("%s",nFichero );
  if(existeFichero(nFichero)==0 ){
    printf("Fichero no encontrado\n" );
    return 0;
  }
  else{
    pasaMayuscula(nFichero);
    printf("Fichero pasado a mayusculas\n" );
  }
  return 0;
}
