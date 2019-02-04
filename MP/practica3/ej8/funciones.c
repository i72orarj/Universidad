#include "funciones.h"

void rellenaFichero(const char* nFichero, int max, int min, int cant){
  srand(time(0));
  int i, a;
  FILE* fichero;
  fichero=fopen(nFichero,"w");
  for(i=0;i<cant;i++){
    a=(rand()%(max-min))+min;
    fprintf(fichero, "%i\n",a );
  }
fclose(fichero);
}

float mediaPares(const char* nFichero){
  int i, sum=0, cant=0, num;
  float media;
  FILE* fichero;
  fichero=fopen(nFichero,"r");
  if(fichero==NULL){
    printf("No se puede acceder al fichero\n" );
    exit -1;
  }
  while(fscanf(fichero,"%d",&num)!=EOF){
    fscanf(fichero,"%d",&num);
    if(num%2==0){
      sum=sum+num;
      cant++;
    }
  }
  media=sum/cant;
  fclose(fichero);
  return media;
}
