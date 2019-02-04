#include "funciones.h"

int main(int argc, char const *argv[]) {
  struct monomio* cabeza=NULL;
  int coeficiente;
  int exponente;
  int opcion;
  int n;
  while(opcion!=0){
    printf("###################################################\n" );
    printf("  1.- Añadir monomio\n" );
    printf("  2.- Eliminar monomio\n" );
    printf("  3.- Evaluar polinomio\n" );
    printf("  4.- Mostrar polinomio\n" );
    printf("  0.- Salir\n" );
    printf("###################################################\n" );
    printf("Opcion: " );
    scanf("%d",&opcion );
    switch (opcion) {
      case 1:
        printf("Coeficiente: " );
        scanf("%d",&coeficiente );
        printf("Exponente: " );
        scanf("%d",&exponente );
        anadeMonomio(&cabeza,coeficiente,exponente);
      break;
      case 2:
        printf("Coeficiente: " );
        scanf("%d",&coeficiente );
        printf("Exponente: " );
        scanf("%d",&exponente );
        eliminaMonomio(&cabeza,coeficiente,exponente);
      break;
      case 3:
        printf("Valor para evaluar: " );
        scanf("%d",&n );
        printf("Resultado: %d\n",evaluaPolinomio(cabeza,n) );
      break;
      case 4:
        imprimirLista(cabeza);
      break;
    }
  }
  return 0;
}
