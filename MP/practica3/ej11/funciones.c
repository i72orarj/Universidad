#include "funciones.h"

int* reservaVector(int cant, int extSup, int extInf){
  srand(time(0));
  int i;
  int* v=(int*)malloc(cant*sizeof(int));
  if(v==NULL){
    printf("Error al crear el vector\n" );
    exit -1;
  }
  else{
    for(i=0;i<cant;i++){
      v[i]=(rand()%(extSup-extInf))+extInf;
    }
    return v;
  }
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

int* rellenaVector(int cant, char* nFichero){
  int* v=(int*)malloc(cant*sizeof(int));
  int num,i=0;
  if(v==NULL){
    printf("Error al crear el vector\n" );
    exit -1;
  }
  else{
    FILE* fichero=fopen(nFichero,"rb");
    if(fichero==NULL){
      printf("Error al abrir el fichero\n" );
      exit -1;
    }
    else{
      while(fread(&num,sizeof(int),1,fichero)>0){
        v[i]=num;
        i++;
      }
    }
  }
return v;
}

float mediaAleatoriosPares(int cant, int* v){
  float media;
  int sum=0,i,num=0;
  for(i=0;i<cant;i++){
    if(v[i]%2==0){
      sum=sum+v[i];
      num++;
    }
  }
  media=sum/num;
  return media;
}
