#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void escribeMatriz(int** matriz,int nFil, int nCol);

void imprimeMatriz(int** matriz, int nFil,int nCol);

void calculaPosicion(int** matriz,int nFil, int nCol, int* filMenor, int* colMenor);

void muestraResultado(int** matriz,int filMenor, int colMenor );
