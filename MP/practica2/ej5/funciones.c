#include "funciones.h"

int cantPalabras(char *frase){
  int palabras=0;
  int tam=strlen(frase);
  if(frase[tam-1]!=' '){
    frase[tam]=' ';
  }
  for(int i=0;i<=tam;i++){
    if(frase[i]==' '){
      palabras++;
    }
  }
  if(frase[tam]==' '){
    frase[tam]='\0';
  }
  return palabras;
}
char** reservaMemoria(int palabras){
  char** vector=(char*)malloc(palabras*sizeof(char));
  if(vector==NULL){
    printf("Error al reservar memoria\n" );
    exit(-1);
    }
  for(int i=0;i<palabras;i++){
    vector[i]=(char*)malloc(PALABRA_STR*sizeof(char));
    if(vector[i]==NULL){
      printf("Error al reservar memoria\n" );
      exit(-1);
    }
  }
    return vector;
}
void rellenaVector(char** vector, char* frase){
  int tam, i, j, k;
  tam=strlen(frase);
  j=0;
  k=0;
  for( i=0;i<tam;i++){
    if(frase[i]==' '){
      i++;
      j++;
      k=0;
    }
    vector[j][k]=frase[i];
    k++;
  }

}
void imprimeVector(char** vector, int palabras){
  int i;
  for(i=0;i<palabras;i++){
    printf("<%s>\n",vector[i] );
  }
}
void mediaMayorMenor(char** vector,float* media,int* mayor, int* menor, int palabras){
    int sum=0;
    int i;
    *mayor=strlen(vector[0]);
    *menor=strlen(vector[0]);
    for(i=0;i<palabras;i++){
      sum=sum+strlen(vector[i]);
      if(strlen(vector[i])>*mayor){
        *mayor=strlen(vector[i]);
      }
      if(*menor>strlen(vector[i])){
        *menor=strlen(vector[i]);
      }
    }
    *media=sum/palabras;
}
void liberaMemoria(char** vector, int palabras){
  int i;
  for(i=0;i<palabras;i++){
    free(vector[i]);
    vector[i]==NULL;
  }
  free(vector);
  vector=NULL;
}
