#include "funciones.h"

int comprobarExistencia(char* nFichero){
  char titulo[MAX_STR];
  libro buscado;
  int a;
  FILE* fichero;
  fichero=fopen(nFichero,"rb");
  if(fichero==NULL){
    printf("Error al abrir el fichero\n" );
    exit -1;
  }
  else{
    printf("Introduzca el titulo que desea buscar\n" );
    scanf("%s",titulo );
    while(fread(&buscado,sizeof(libro),1,fichero)>0){
      a=strcmp(buscado.titulo,titulo);
      if(a==0){
        fclose(fichero);
        return 1;
      }
    }
    fclose(fichero);
    return 0;
  }
}

void nuevoLibro(char* nFichero){
  libro nuevo;
  FILE* fichero;
  fichero=fopen(nFichero,"ab");
  if(fichero==NULL){
    printf("Error al abrir el fichero\n" );
    exit -1;
  }
  else{
    printf("Introduzca el titulo\n");
    scanf("%s",nuevo.titulo );
    printf("Introduzca el autor\n" );
    scanf("%s",nuevo.autor);
    printf("Introduzca el precio\n" );
    scanf("%f",&nuevo.precio);
    printf("Introduzca las unidades\n" );
    scanf("%d",&nuevo.unidades );
    fwrite(&nuevo,sizeof(libro),1,fichero);
  }
  fclose(fichero);
}

int numeroLibros(char* nFichero){
  FILE* fichero;
  libro leido;
  int cont=0;
  fichero=fopen(nFichero,"rb");
  if(fichero==NULL){
    printf("Error al abrir el fichero\n" );
    exit -1;
  }
  else{
    while(fread(&leido,sizeof(libro),1,fichero)>0){
      cont++;
    }
  }
  fclose(fichero);
  return cont;
}

void listaLibros(char* nFichero){
  libro leido;
  FILE* fichero;
  fichero=fopen(nFichero,"rb");
  if(fichero==NULL){
    printf("Error al abrir el fichero\n");
    exit -1;
  }
  else{
    while(fread(&leido,sizeof(libro),1,fichero)>0){
      printf("Titulo: %s\n",leido.titulo );
      printf("Autor: %s\n",leido.autor );
      printf("Precio: %2.f\n",leido.precio );
      printf("Unidades: %d\n\n",leido.unidades );
    }
  }
fclose(fichero);
}

void vendeLibro(char* nFichero){
  FILE* fichero;
  FILE* copia;
  libro leido;
  char titulo[MAX_STR];
  int a;
  fichero=fopen(nFichero,"rb");
  if(fichero==NULL){
    printf("Error al abrir el fichero\n" );
    exit -1;
  }
  else{
    copia=fopen("copia.txt","wb");
    if(copia==NULL){
      printf("Error al crear el fichero\n" );
      exit -1;
    }
    else{
      printf("Introduzca el titulo del libro\n" );
      scanf("%s",titulo );
      while(fread(&leido,sizeof(libro),1,fichero)>0){
        a=strcmp(leido.titulo,titulo);
        if(a==0){
          leido.unidades=leido.unidades-1;
          fwrite(&leido,sizeof(libro),1,copia);
        }
        else{
          fwrite(&leido,sizeof(libro),1,copia);
        }
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
  libro leido;
  fichero=fopen(nFichero,"rb");
  if(fichero==NULL){
    printf("Error al abrir el fichero\n" );
    exit -1;
  }
  else{
    copia=fopen("copia.txt","wb");
    if(copia==NULL){
      printf("Error al abrir el fichero\n");
      exit -1;
    }
    else{
      while(fread(&leido,sizeof(libro),1,fichero)>0){
        if(leido.unidades>0){
          fwrite(&leido,sizeof(libro),1,copia);
        }
      }
    }
  }
fclose(fichero);
fclose(copia);
remove(nFichero);
rename("copia.txt",nFichero);
}
