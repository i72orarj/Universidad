#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct param {
  int* iniciov1;
  int* iniciov2;
  int n;
}param;

void multiplica(param* parametros ){
  int* result=(int*)malloc(sizeof(int));
  int i;
  *result=0;
  for(i=0;i<parametros->n;i++){
    *result+=parametros->iniciov1[i]*parametros->iniciov2[i];
  }
  pthread_exit(result);
}


int main(int argc, char const *argv[]) {
  srand(time(NULL));
  int n,m,i;
  int* devuelve;
  int resultado=0;
  printf("Introduzca numero de hilos\n" );
  scanf("%d",&m );
  pthread_t hilos[m];
  param param[m];
  printf("Introduzca numero de elementos de los vectores\n" );
  scanf("%d",&n );
  int v1[n],v2[n];
  for(i=0;i<n;i++){
    v1[i]=rand()%10;
    v2[i]=rand()%10;
  }
  int parte=n/m,resto=n%m;
  for(i=0;i<m;i++){
    if(i==m-1){
      param[i].iniciov1=&v1[i*parte];
      param[i].iniciov2=&v2[i*parte];
      param[i].n=parte+resto;
    }
    else{
      param[i].iniciov1=&v1[i*parte];
      param[i].iniciov2=&v2[i*parte];
      param[i].n=parte;
    }
  }
  for(i=0;i<m;i++){
    pthread_create(&hilos[i],NULL,(void*)multiplica,&param[i]);
  }
  for(i=0;i<m;i++){
    pthread_join(hilos[i],(void**)&devuelve);
    resultado+=*devuelve;
  }
  printf("El resultado es %d\n",resultado );
  return 0;
}
