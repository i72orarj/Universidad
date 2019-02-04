#include "funciones.h"

int main(int argc, char const *argv[]) {
  char nFichero[MAX_STR];
  int max, min, cant;
  printf("Nombre del fichero a crear: ");
  scanf("%s",nFichero );
  printf("Valor maximo a alcanzar: " );
  scanf("%d",&max);
  printf("Valor minimo: " );
  scanf("%d",&min );
  printf("Cantidad de numeros que desea en el fichero: " );
  scanf("%d",&cant );
  rellenaFichero(nFichero,max,min,cant);
  printf("Fichero <%s> creado y rellenado\n" ,nFichero);
  return 0;
}
