#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int m[3][3];
int v[3];

void* multiplica(int* j){
  int* result=(int*)malloc(sizeof(int));
  *result=0;
  int a,b;
  for(int i=0;i<3;i++){
    a=m[i][*j];
    b=v[i];
    *result+=a*b;
  }
  pthread_exit(result);
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  pthread_t hilos[3];
  int i,j;
  int* devuelve;
  int resultado=0;
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      m[i][j]=rand()%10;
      printf("%d\t",m[i][j] );
    }
    printf("\n" );
  }
  for(i=0;i<3;i++){
    v[i]=rand()%10;
    printf("%d\t",v[i] );
  }
  printf("\n" );
  for(i=0;i<3;i++){
    pthread_create(&hilos[i],NULL,(void*)multiplica,&i);
  }
  for(i=0;i<3;i++){
    pthread_join(hilos[i],(void**)&devuelve);
    resultado+=*devuelve;
  }
  printf("Resultado=%d\n",resultado );

  return 0;
}
