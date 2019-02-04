#include "funciones.h"

int main(int argc, char const *argv[]) {
  int nFil, nCol, filMenor, colMenor;
  printf("Introduzca el numero de filas de la matriz\n");
  scanf("%i",&nFil );
  printf("Introduzca el numero de columnas de la matriz\n");
  scanf("%i",&nCol );
  int** matriz=(int*)malloc(nFil*sizeof(int));
  if(matriz==NULL){
    printf("fallo\n" );
    return 0;
  }
  for(int i=0;i<nFil;i++){
    matriz[i]=(int*)malloc(nCol*sizeof(int));
    if(matriz[i]==NULL){
      printf("fallo\n" );
      return 0;
    }
  }
  escribeMatriz(matriz,nFil,nCol);
  imprimeMatriz(matriz,nFil,nCol);
  calculaPosicion(matriz,nFil,nCol,&filMenor,&colMenor);
  muestraResultado(matriz,filMenor,colMenor );
  free(matriz);
  //falta for por cada fila antes del free
  matriz==NULL;
  return 0;
}
