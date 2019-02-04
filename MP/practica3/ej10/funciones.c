#include "funciones.h"

int* reservaVector(int cant, int extSup, int extInf){
  srand(time(0));
  int i;
  int* v=(int*)malloc(cant*sizeof(int));
  for(i=0;i<cant;i++){
    v[i]=(rand()%(extSup-extInf))+extInf;
  }
  return v;
}

void escribeFichero(int* v,int cant,char* nFichero){
  FILE* fichero;
  int i,num;
  fichero=fopen(nFichero,"wb");
  if(fichero==NULL){
    printf("No se puede abrir el fichero\n" );
    exit -1;
  }
  else{
    for(i=0;i<cant;i++){
      num=v[i];
      fwrite(&num,sizeof(int),1,fichero);
    }
  }
fclose(fichero);
}
