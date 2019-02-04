#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **reservarMemoria(int nFil, int nCol);
void rellenaMatriz(int **matriz, int nFil, int nCol);
void imprimeMatriz(int **matriz, int nFil, int nCol);
int *minCol(int **matriz, int nFil, int nCol);
void imprimeVector(int *vector, int nCol);
void liberarMemoria(int **matriz, int nFil);
int** multiplicaMatrices(int** matriz1,int nFil1, int nCol1, int** matriz2, int nFil2, int nCol2);
