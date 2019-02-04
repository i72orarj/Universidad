#include "funciones.h"

void escribeMatriz(int** matriz,int nFil, int nCol){
  srand(time(0));
  for(int i=0;i<nFil;i++){
    for(int j=0;j<nCol;j++){
      matriz[i][j]=rand()%20;
    }
  }
}

void imprimeMatriz(int** matriz, int nFil,int nCol){
  printf("MATRIZ\n" );
  for(int i=0;i<nFil;i++){
    for(int j=0;j<nCol;j++){
      printf("%i\t",matriz[i][j] );
    }
    printf("\n" );
  }
}

void calculaPosicion(int** matriz,int nFil, int nCol, int* filMenor, int* colMenor){
  *filMenor=0;
  *colMenor=0;
  int menor=matriz[0][0];
  for(int i=0;i<nFil;i++){
    for(int j=0;j<nCol;j++){
      if(matriz[i][j]<menor){
        *filMenor=i;
        *colMenor=j;
      }
    }
  }
}

void muestraResultado(int** matriz,int filMenor, int colMenor ){
  printf("El menor valor de la matriz es %i y se encuentra en la fila %i y la columna %i\n",matriz[filMenor][colMenor],filMenor+1,colMenor+1 );
}
