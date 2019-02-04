#include "funciones.h"

struct monomio* nuevoElemento(){
  struct monomio* nuevo=(struct monomio*)malloc(sizeof(struct monomio));
  return nuevo;
}

void anadeMonomio(struct monomio** cabeza, int coeficiente, int exponente){
  struct monomio* nuevo=NULL;
  nuevo=nuevoElemento();
  nuevo->coeficiente=coeficiente;
  nuevo->exponente=exponente;
  nuevo->sig=*cabeza;
  *cabeza=nuevo;
}

void eliminaMonomio(struct monomio** cabeza,int coeficiente, int exponente){
  struct monomio* ant=NULL;
  struct monomio* aux=NULL;
  aux=*cabeza;
  while((aux->coeficiente!=coeficiente) &&(aux->exponente!=exponente)){
    ant=aux;
    aux=aux->sig;
  }
  if(aux==*cabeza){
    *cabeza=aux->sig;
    free(aux);
  }
  else{
    ant->sig=aux->sig;
    free(aux);
  }
}

void imprimirLista(struct monomio *cabeza){
 struct monomio *aux = NULL;

 aux = cabeza;
 if(aux==NULL){
   printf("No existe polinomio\n");
 }
 while (aux != NULL)
  {
   printf("%dx^%d", aux->coeficiente,aux->exponente);
   aux = aux->sig;
   if(aux!=NULL){
     printf("+" );
   }
  }
  printf("\n" );
}
//usar auxiliar para recorrer primero cabeza luego cabeza.sig
int evaluaPolinomio(struct monomio* cabeza, int n){
  int res=0;
  struct monomio* aux=NULL;
  aux=cabeza;
  while(aux!=NULL){
    res=res+(aux->coeficiente)*(pow(n,aux->exponente));
    aux=aux->sig;
  }
  return res;
}
