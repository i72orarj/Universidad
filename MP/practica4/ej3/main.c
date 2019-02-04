#include "funciones.h"

int main(int argc, char const *argv[]) {
  int nEle=cuentaAlumnos();
  alumno* vAlumnos=reservaVector(nEle);
  rellenaVector(vAlumnos,nEle);
  printf("------ANTES-------\n" );
  imprimeVector(vAlumnos,nEle);
  qsort(vAlumnos,nEle,sizeof(alumno),&comparaNota);
  printf("---------DESPUES--------\n" );
  imprimeVector(vAlumnos,nEle);
  return 0;
}
