#include "funciones.h"
#include "pilas.h"

void listarPila(struct nodo** cabeza){
  struct nodo* aux=NULL;
  int codigo;
  while(pilaVacia(*cabeza)==0){
    codigo=pop(cabeza);
    printf("1:%d\t",codigo );
    push(&aux,codigo);
  }
  while(pilaVacia(aux)==0){
    codigo=pop(&aux);
    printf("2:%d\t",codigo );
    push(cabeza,codigo);
  }
}

int comprobarExistencia(struct nodo** cabeza, int codigo){
  struct nodo* aux=NULL;
  int encontrado=0, leido;
  while(pilaVacia(*cabeza)==0){
    leido=pop(cabeza);
    if(leido==codigo){
      encontrado=1;
    }
    push(&aux,codigo);
  }
  while(pilaVacia(aux)==0){
    codigo=pop(&aux);
    push(cabeza,codigo);
  }
  return encontrado;
}

void borrarContenedor(struct nodo** cabeza, int codigo){
  struct nodo* aux=NULL;
  int leido;
  while(pilaVacia(*cabeza)==0){
    codigo=pop(cabeza);
    if(leido!=codigo){
      push(&aux,codigo);
    }
  }
  while(pilaVacia(aux)==0){
    codigo=pop(&aux);
    push(cabeza,codigo);
  }
}
