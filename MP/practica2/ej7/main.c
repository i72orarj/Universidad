#include "funciones.h"
int main() {
  int nFil1, nCol1, nFil2, nCol2;
  printf("Introduzca el numero de filas y columnas de la matriz 1\n");
  scanf("%i",&nFil1);
  scanf("%i",&nCol1);
  int **matriz1=reservarMemoria(nFil1, nCol1);
  printf("Introduzca el numero de filas y columnas de la matriz 2\n");
  scanf("%i",&nFil2);
  scanf("%i",&nCol2);
  int **matriz2=reservarMemoria(nFil2, nCol2);
  printf("MATRICES CREADAS\n");
  if(nCol1!=nFil2){
    printf("NO SE PUEDE HACER LA MULTIPLICACION\n");
    return 0;
  }
  rellenaMatriz(matriz1, nFil1, nCol1);
  printf("MATRIZ 1 RELLENADA\n" );
  imprimeMatriz(matriz1,nFil1,nCol1);
  rellenaMatriz(matriz2, nFil2, nCol2);
  printf("MATRIZ 2 RELLENADA\n" );
  imprimeMatriz(matriz2, nFil2, nCol2);
  int** matrizMult=multiplicaMatrices(matriz1, nFil1, nCol1, matriz2, nFil2, nCol2);
  printf("IMPRIMIENDO MATRIZ MULTIPLICADA\n");
  imprimeMatriz(matrizMult,nFil1, nCol2);
  liberarMemoria(matriz1, nFil1);
  liberarMemoria(matriz2, nFil2);
  liberarMemoria(matrizMult,nFil1);
  return 0;
}
