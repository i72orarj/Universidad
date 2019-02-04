#include "funciones.h"

int main(int argc, char const *argv[]) {
  int palabras=0;
  char frase[MAX_STR];
  printf("Introduzca una frase\n" );
  gets(frase);
  palabras=cantPalabras(frase);
  printf("Hay %d palabras\n",palabras );
  char** vPalabras=reservaMemoria(palabras);
  printf("Vector reservado\n" );
  rellenaVector(vPalabras,frase);
  printf("Vector rellenado\n" );
  printf("Imprimiendo vector\n" );
  imprimeVector(vPalabras,palabras);
  float media;
  int mayor,menor;
  mediaMayorMenor(vPalabras,&media,&mayor, &menor,palabras);
  printf("La media de longitud de las palabras es: %f\n",media );
  printf("La mayor longitud es: %d\n",mayor );
  printf("La menor longitud es: %d\n",menor);
  liberaMemoria(vPalabras,palabras);

  return 0;
}
