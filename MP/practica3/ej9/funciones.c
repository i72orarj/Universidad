#include "funciones.h"

int comprobarExistencia(char* nFichero){
  char titulo[MAX_STR];
  char aux[MAX_STR];
  int res;
  FILE* fichero;
  fichero=fopen(nFichero,"r");
  if(fichero==NULL){
    printf("No se puede abrir el fichero\n" );
    exit -1;
  }
  else{
    printf("Introduzca el titulo del libro\n" );
    scanf("%s",titulo );
    while(fscanf(fichero,"%s",aux)!=EOF){
      //fscanf(fichero,"%s",aux);
      res =strcmp(titulo,aux);
      if(res==0){
        return 1;
      }
  }
}
  return 0;
}

void nuevoLibro(char* nFichero){
  char titulo[MAX_STR];
  char autor[MAX_STR];
  float precio;
  int unidades;
  FILE* fichero;
  fichero=fopen(nFichero,"a");
  if(fichero==NULL){
    printf("Fichero no encontrado\n" );
    exit-1;
  }
  else{
  printf("Introduzca el titulo:" );
  scanf("%s",titulo );
  fprintf(fichero, "%s\n",titulo);
  printf("Introduzca el autor:" );
  scanf("%s",autor );
  fprintf(fichero, "%s\n",autor );
  printf("Introduzca el precio:" );
  scanf("%f",&precio );
  fprintf(fichero, "%.2f",precio );
  printf("Introduzca las unidades:" );
  scanf("%d",&unidades );
  fprintf(fichero, " %d\n",unidades );
  printf("Libro añadido\n" );
}
fclose(fichero);
}
int numeroLibros(char* nFichero){
  int cont=0;
  char linea[MAX_STR];
  FILE* fichero;
  fichero=fopen(nFichero,"r");
  if(fichero==NULL){
    printf("Fichero no encontrado\n" );
    exit -1;
  }
  else{
    while(fscanf(fichero,"%s",linea)!=EOF){
      cont++;
    }
  }
  fclose(fichero);
return cont/4;
}

void listaLibros(char* nFichero){
  char titulo[MAX_STR];
  char autor[MAX_STR];
  float precio;
  int unidades;
//  libro* vLibros;
//  vLibros=(libro*)malloc()
  FILE* fichero;
  fichero=fopen(nFichero,"r");
  if(fichero==NULL){
    printf("Fichero no encontrado" );
    exit -1;
  }
  else{
    while(fscanf(fichero,"%s",titulo)!=EOF){
      //fscanf(nFichero,"%s",titulo);
      printf("Titulo: %s\n",titulo );
      fscanf(fichero, "%s",autor);
      printf("Autor: %s\n",autor );
      fscanf(fichero,"%f %d",&precio,&unidades);
      printf("Precio: %2.f Unidades: %d\n\n",precio,unidades );
    }
  }

fclose(fichero);
}

void vendeLibro(char *nFichero){
  FILE* fichero;
  FILE* copia;
  char borra[MAX_STR];
  char titulo[MAX_STR];
  char autor[MAX_STR];
  float precio;
  int unidades;
  int res;
  fichero=fopen(nFichero,"r");
  if(fichero==NULL){
    printf("Fichero no encontrado\n");
    exit -1;
  }
  copia=fopen("copia.txt","w");
  if(copia==NULL){
    printf("Error al crear el fichero\n" );
    exit -1;
  }
  else{
    printf("Introduzca el titulo del libro\n" );
    scanf("%s",borra );
    while(fscanf(fichero,"%s",titulo)!=EOF){
        res=strcmp(titulo,borra);
        if(res==0){
          fscanf(fichero,"%s",autor);
          fscanf(fichero,"%f %d",&precio,&unidades);
          if(unidades>0){
            fprintf(copia, "%s\n",titulo );
            fprintf(copia, "%s\n", autor);
            fprintf(copia, "%2.f %d\n",precio,unidades-1 );
          }
          if(unidades==0){
            printf("El libro tiene 0 unidades en stock\nSi desea puede eliminarlo\n");
            fprintf(copia, "%s\n",titulo );
            fprintf(copia, "%s\n", autor);
            fprintf(copia, "%2.f %d\n",precio,unidades);
          }
        }
        else{
          fprintf(copia, "%s\n",titulo );
          fscanf(fichero,"%s",autor);
          fprintf(copia, "%s\n", autor);
          fscanf(fichero,"%f %d",&precio,&unidades);
          fprintf(copia, "%2.f %d\n",precio,unidades);
        }
      }
  }
fclose(fichero);
fclose(copia);
remove(nFichero);
rename("copia.txt",nFichero);
}

void eliminaLibro(char* nFichero){
  FILE* fichero;
  FILE* copia;
  char titulo[MAX_STR];
  char autor[MAX_STR];
  float precio;
  int unidades;
  int cont=0;
  fichero=fopen(nFichero, "r");
  if(fichero==NULL){
    printf("Fichero no encontrado\n");
    exit -1;
  }
  copia=fopen("copia.txt","w");
  if(copia==NULL){
    printf("Error al crear el fichero\n" );
    exit -1;
  }
  else{
    while(fscanf(fichero,"%s",titulo)!=EOF){
      fscanf(fichero,"%s",autor);
      fscanf(fichero,"%f %d",&precio,&unidades);
      if(unidades!=0){
        fprintf(copia, "%s\n",titulo );
        fprintf(copia, "%s\n",autor );
        fprintf(copia, "%2.f %d\n",precio, unidades );
      }
      else{
        cont++;
      }
    }
  }
fclose(fichero);
fclose(copia);
remove(nFichero);
rename("copia.txt",nFichero);
if(cont==1){
  printf("%d libro eliminado\n",cont );
}
else{
  printf("%d libros eliminados\n",cont );
}
}
