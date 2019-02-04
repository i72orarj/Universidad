#include "funciones.h"
#include "pilas.h"


int main(int argc, char const *argv[]) {
  struct nodo* cabeza=NULL;
  int nPilas;
  int codigo;
  int i;
  int opcion=1;
  while(opcion!=0){
    printf("\n###################################################\n" );
    printf(" 1.- Crear pila de N contenedores\n" );
    printf(" 2.- Listar pila\n" );
    printf(" 3.- Comprobar existencia de contenedor en la pila\n" );
    printf(" 4.- Eliminar contenedor de la pila\n" );
    printf(" 0.- Salir\n" );
    printf("###################################################\n" );
    printf("\nOpcion: " );
    scanf("%d",&opcion );
    printf("\n");
    switch (opcion) {
      case 1:
        printf("Indique la cantidad de contenedores: " );
        scanf("%d",&nPilas );
        for(i=0;i<nPilas;i++){
          printf("Introduzca el codigo del contenedor: " );
          scanf("%d",&codigo);
          printf("\t\t\t\t\tcodigo:%d\n", codigo);
          if(comprobarExistencia(&cabeza,codigo)==1){
            printf("El contenedor %d se encuentra en la pila\n",codigo );
            i--;
          }
          else{
            push(&cabeza,codigo);
            cabeza=cabeza->sig;
          }
        }

      break;
      case 2:
        listarPila(&cabeza);
      break;
      case 3:
        printf("Indique el codigo del contenedor: " );
        scanf("%d",&codigo );
        if(comprobarExistencia(&cabeza,codigo)==1){
          printf("El contenedor %d se encuentra en la pila\n",codigo );
        }
        else{
          printf("El contenedor %d no se encuentra en la pila\n",codigo );
        }
      break;
      case 4:
        printf("Indique el codigo del contenedor: " );
        scanf("%d",&codigo );
        if(comprobarExistencia(&cabeza,codigo)==1){
          borrarContenedor(&cabeza,codigo);
        }
        else{
          printf("El contenedor %d no se encuentra en la pila\n",codigo );
        }
      break;
    }
  }
  return 0;
}
