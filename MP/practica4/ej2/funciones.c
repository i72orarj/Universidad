#include "funciones.h"

alumno* reservaVector(int nEle){
  alumno* v=(alumno*)malloc(nEle*sizeof(alumno));
  if(v==NULL){
    printf("Error al reservar el vector\n");
    exit(-1);
  }
  return v;
}

int cuentaAlumnos(char* nFichero){
  int cont=0;
  alumno ficha;
  FILE* fichero;
  fichero=fopen(nFichero,"rb");
  if(fichero==NULL){
    printf("Error al abrir el fichero\n");
    exit(-1);
  }
  fread(&ficha,sizeof(alumno),1,fichero);
  while (!feof(fichero)){
     cont++;
     fread(&ficha,sizeof(alumno),1,fichero);
  }
  fclose(fichero);
  return cont;
}

void rellenaVector(alumno* vector, int nEle, char* nFichero){
  int i=0;
  alumno ficha;
  FILE* fichero;
  fichero=fopen(nFichero,"rb");
  if(fichero==NULL){
    printf("Error al abrir el fichero\n");
    exit(-1);
  }
//  fread(&ficha,sizeof(alumno),1,fichero);
  while (!feof(fichero)&&i<nEle){
    fread(&ficha,sizeof(alumno),1,fichero);
    vector[i]=ficha;;
    i++;
  }
  fclose(fichero);
}

void ordenaVector(alumno* vector, int nEle){
  int i,j,minimo,aux;
  for(i=0;i<nEle;i++){
     minimo=i;
     for(j=i+1;j<nEle-1;j++){
        if (vector[minimo].DNI > vector[j].DNI)
           minimo=j;
     aux=vector[minimo].DNI;
     vector[minimo].DNI=vector[i].DNI;
     vector[i].DNI=aux;
    }
  }
}

void imprimeVector(alumno* vector, int nEle){
  int i;
  for(i=0;i<nEle;i++){
    printf("Nombre: %s\n",vector[i].nombre);
    printf("DNI: %d\n",vector[i].DNI );
    printf("Nota: %f\n",vector[i].nota );
    printf("\n" );
  }
}
