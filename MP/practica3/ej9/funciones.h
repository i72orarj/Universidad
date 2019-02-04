#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 30

typedef struct libro {
  char titulo[MAX_STR];
  char autor[MAX_STR];
  float precio;
  int unidades;
}libro;

int comprobarExistencia(char* nFichero);

void nuevoLibro(char* nFichero);

int numeroLibros(char* nFichero);

void listaLibros(char* nFichero);

void vendeLibro(char *nFichero);

void eliminaLibro(char* nFichero);
