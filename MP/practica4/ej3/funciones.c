#include "funciones.h"

alumno* reservaVector(int nEle){
  alumno* v=(alumno*)malloc(nEle*sizeof(alumno));
  if(v==NULL){
    printf("Error al reservar el vector\n");
    exit(-1);
  }
  return v;
}

int cuentaAlumnos(){
  int cont=0;
  alumno ficha;
  FILE* fichero;
  fichero=fopen("../ej2/alumnos.bin","rb");
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

void rellenaVector(alumno* vector, int nEle){
  int i=0;
  alumno ficha;
  FILE* fichero;
  fichero=fopen("../ej2/alumnos.bin","rb");
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

int comparaNota(const void* e1, const void* e2){
  alumno* a,*b;
  a=(alumno*)e1;
  b=(alumno*)e2;
  if((*a).nota<(*b).nota){
    return -1;
  }
  else{
    if((*a).nota==(*b).nota){
      return 0;
    }
    else{
      return 1;
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
