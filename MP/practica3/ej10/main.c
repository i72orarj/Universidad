#include "funciones.h"

int main(int argc, char const *argv[]) {
  char nFichero[MAX_STR];
  int cant,extSup, extInf;
  if(argc!=5){
    printf("Cantidad incorrecta de argumentos\n(./nombre nombre_fichero cantidad_elementos extremo_sup extremo_inf)\n" );
    return 0;
  }
  else{
    strcpy(nFichero,argv[1]);
    cant=atoi(argv[2]);
    extSup=atoi(argv[3]);
    extInf=atoi(argv[4]);
    int* vectorAleatorios;
    vectorAleatorios=reservaVector(cant,extSup,extInf);
    escribeFichero(vectorAleatorios,cant,nFichero);
    printf("Fichero creado y rellenado\n" );
  }
  return 0;
}
