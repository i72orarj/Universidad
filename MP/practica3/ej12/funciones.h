#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX_STR
#define MAX_STR 30
#endif

typedef struct libro {
  char titulo[100];
  char autor[50];
  float precio;
  int unidades;
}libro;

int comprobarExistencia(char* nFichero);

void nuevoLibro(char* nFichero);

int numeroLibros(char* nFichero);

void listaLibros(char* nFichero);

void vendeLibro(char* nFichero);

void eliminaLibro(char* nFichero);
