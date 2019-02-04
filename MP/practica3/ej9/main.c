#include "funciones.h"

int main(int argc, char const *argv[]) {
  int op_menu;
  char nFichero[MAX_STR];
  if(argc!=2){
    printf("Cantidad incorrecta de argumentos\n" );
    return 0;
  }
  strcpy(nFichero,argv[1]);
  do {
    printf("\n------MENU------\n\n" );
    printf("1.- Comprobar la existencia de un libro en el stock\n" );
    printf("2.- Introducir nuevo libro en el stock\n" );
    printf("3.- Contar el número de libros diferentes que hay en el stock\n" );
    printf("4.- Listar libros almacenados en el stock\n" );
    printf("5.- Vender libro\n" );
    printf("6.- Borrar registros con 0 unidades\n" );
    printf("0.- Salir\n" );
    printf("Opcion:" );
    scanf("%d",&op_menu );
    printf("\n" );
    switch (op_menu) {
      case 1:
      if(comprobarExistencia(nFichero)==1){
          printf("Existe el libro buscado\n" );
        }
        else{
          printf("No existe el libro buscado\n" );
        }
        break;
      case 2:
        nuevoLibro(nFichero);
        break;
      case 3:
        printf("Actualmente existen %d libros diferentes en el stock\n",numeroLibros(nFichero));
        break;
      case 4:
        listaLibros(nFichero);
        break;
      case 5:
        vendeLibro(nFichero);
        break;
      case 6:
        eliminaLibro(nFichero);
        break;
    }
  } while(op_menu!=0);
  printf("Fin del programa\n" );
  return 0;
}
