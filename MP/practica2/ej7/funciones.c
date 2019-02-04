#include "funciones.h"

int **reservarMemoria(int nFil, int nCol){
  int **matriz=(int*)malloc(nFil*sizeof(int));
  if(matriz==NULL){
    printf("Error");
  }
  for(int i=0;i<nCol;i++){
    matriz[i]=(int*)malloc(nCol*sizeof(int));
    if(matriz[i]==NULL){
      printf("Error");
    }
  }
  return matriz;
}
void rellenaMatriz(int **matriz, int nFil, int nCol){
  srand(time(0));
  for(int i=0; i<nFil;i++){
    for(int j=0;j<nCol;j++){
        matriz[i][j]=(rand()%20)+1;
    }
  }
}
void imprimeMatriz(int **matriz, int nFil, int nCol){
  for(int i=0; i<nFil;i++){
    for(int j=0;j<nCol;j++){
      printf("\t%i\t",matriz[i][j]);
    }
  printf("\n" );
  }
}
int *minCol(int **matriz, int nFil, int nCol){
  int *vector=(int*)malloc(nFil*sizeof(int));
  int min;
  for(int j=0;j<nCol;j++){
    min=matriz[0][j];
      for(int i=0;i<nFil;i++){
        if(matriz[i][j]<min){
          min=matriz[i][j];
        }
      }
    vector[j]=min;
  }
  return  vector;
}
void imprimeVector(int *vector, int nCol){
  for(int i=0;i<nCol;i++){
    printf("\nMinimo de la columna %i =%i\n", i+1,vector[i]);
  }
}
void liberarMemoria(int **matriz, int nFil){
  free(matriz);
  matriz==NULL;
}
int** multiplicaMatrices(int** matriz1,int nFil1, int nCol1, int** matriz2, int nFil2, int nCol2){
  int **matrizMult=(int*)malloc(nFil1*sizeof(int));
  if(matrizMult==NULL){
    printf("Error");
  }
  for(int i=0;i<nCol2;i++){
    matrizMult[i]=(int*)malloc(nCol2*sizeof(int));
    if(matrizMult[i]==NULL){
      printf("Error");
    }
  }
  for(int a=0; a<nFil1;a++){
    for(int b=0; b<nCol2; b++){
      matrizMult[a][b]=0;
      for(int c=0;c<nCol1;c++){
        matrizMult[a][b]=matrizMult[a][b]+matriz1[a][c]*matriz2[c][b];
      }
    }
  }
  return matrizMult;
}
