#include "funciones.h"

int existeFichero(char* nFichero){
  FILE* fichero;
  fichero=fopen(nFichero,"r");
  if(fichero==NULL){
    fclose(fichero);
    return 0;
  }
  else{
    fclose(fichero);
    return 1;
  }
}
void pasaMayuscula(char* nFichero){
  FILE* ficheroMin;
  FILE* ficheroMay;
  char palabra[MAX_STR];
  ficheroMin=fopen(nFichero,"r");
  ficheroMay=fopen("mayusculas-nombreFicheroDeEntrada.txt","w");
  if(ficheroMin==NULL){
    exit (-1);
  }
  else{
    while(fscanf(ficheroMin,"%s",palabra)!=EOF){
      //fscanf(ficheroMin,"%s",palabra);
      for(int i=0;i<strlen(palabra);i++){
        palabra[i]=toupper(palabra[i]);
      }
      fprintf(ficheroMay, "%s ",palabra);
    }
  }

  fclose(ficheroMay);
  fclose(ficheroMin);
}
