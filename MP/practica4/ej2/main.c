#include "funciones.h"

int main(int argc, char const *argv[]) {
  if(argc!=3){
    printf("Cantidad erronea de argumentos\n" );
    return 0;
  }
  int orden=atoi(argv[1]);
  if((orden!=1) && (orden!=0)){
    printf("Orden de ordenacion incorrecto\n" );
    printf("\t0:Descendente\n\t1:Ascendente\n");
    return 0;
  }
  if(orden==1){

  }
  else{
    
  }
  int nEle;
  char nFichero[MAX_STR];
  strcpy(nFichero,argv[2]);
  nEle=cuentaAlumnos(nFichero);
  alumno* vector=reservaVector(nEle);
  rellenaVector(vector,nEle,nFichero);
  imprimeVector(vector,nEle);
  ordenaVector(vector,nEle);
  printf("Despuess----------------------------------------\n" );
  imprimeVector(vector,nEle);

  return 0;
}
