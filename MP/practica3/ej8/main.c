#include "funciones.h"

int main(int argc, char const *argv[]) {
  char nFichero[MAX_STR];
  float media;
  int max,min,cant;
  if(argc!=2){
    printf("Cantidad erronea de argumentos\n" );
    return 0;
  }
  else{
    strcpy(nFichero,argv[1]);
    printf("Valor maximo a alcanzar: " );
    scanf("%d",&max);
    printf("Valor minimo: " );
    scanf("%d",&min );
    printf("Cantidad de numeros que desea en el fichero: " );
    scanf("%d",&cant );
    rellenaFichero(nFichero,max,min,cant);
    printf("Fichero creado y rellenado\n" );
    media=mediaPares(nFichero);
    printf("La media de los numeros pares del fichero es: %.2f\n",media );
  }
  return 0;
}
