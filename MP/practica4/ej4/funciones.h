#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct monomio {
  int coeficiente;
  int exponente;
  struct monomio* sig;
};

struct monomio* nuevoElemento();

void anadeMonomio(struct monomio** cabeza, int coeficiente, int exponente);

void eliminaMonomio(struct monomio** cabeza,int coeficiente, int exponente);

void imprimirLista(struct monomio *cabeza);

int evaluaPolinomio(struct monomio* cabeza, int n);
