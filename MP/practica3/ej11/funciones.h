#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef MAX_STR
#define MAX_STR 30
#endif

int* reservaVector(int cant, int extSup, int extInf);

void escribeFichero(int* v,int cant,char* nFichero);

int* rellenaVector(int cant, char* nFichero);

float mediaAleatoriosPares(int cant, int* v);
