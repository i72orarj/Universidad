#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX_STR
#define MAX_STR 30
#endif

typedef struct Ficha_alumno {
   char nombre[50];
   int DNI;
   float nota;
}alumno;

alumno* reservaVector(int nEle);

int cuentaAlumnos(char* nFichero);

void rellenaVector(alumno* vector, int nEle, char* nFichero);

void ordenaVector(alumno* vector, int nEle);

void imprimeVector(alumno* vector, int nEle);
