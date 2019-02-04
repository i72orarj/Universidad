#include "funciones.h"

void rellenaFichero(char* nFichero, int max, int min, int cant){
  srand(time(0));
  int i, a;
  FILE* fichero;
  fichero=fopen(nFichero,"w");
  for(i=0;i<cant;i++){
    a=(rand()%(max-min))+min;
    fprintf(fichero, "%d\n",a );
  }
}
