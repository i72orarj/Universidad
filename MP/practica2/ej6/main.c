#include "funciones.h"

  int main() {
    int nFil,nCol;
    printf("Introduzca el numero de filas y columnas\n");
    scanf("%i %i",&nFil,&nCol);
    getchar();
  //  printf("Introduzca el numero de columnas\n");
  //  scanf("%i",&nCol);
    printf("\nRESERVANDO MEMORIA\n\n");
    int **matriz=reservarMemoria(nFil,nCol);
    rellenaMatriz(matriz,nFil,nCol);
    printf("IMPRIMIENDO MATRIZ\n\n");
    imprimeMatriz(matriz,nFil,nCol);
    int *vector=minCol(matriz,nFil,nCol);
    printf("\n" );
    imprimeVector(vector,nCol);
    liberarMemoria(matriz,nFil);
    return 0;
  }
