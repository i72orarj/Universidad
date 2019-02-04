#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR 256
#define PALABRA_STR 30

int cantPalabras(char* frase);

char** reservaMemoria(int palabras);

void rellenaVector(char** vector, char* frase);

void imprimeVector(char** vector, int palabras);

void mediaMayorMenor(char** vector,float* media,int* mayor, int* menor, int palabras);

void liberaMemoria(char** vector, int palabras);
