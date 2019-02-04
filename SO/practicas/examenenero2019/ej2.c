#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int vector[10];
pthread_mutex_t sem=PTHREAD_MUTEX_INITIALIZER;

void generaAleatorios(int* a){
  int* sum=(int*)malloc(sizeof(int));
  int index=*a;
  int i,j;
  *sum=0;
  for(j=0;j<100;j++){
    i=rand()%10;
    pthread_mutex_lock(&sem);
    //printf("Trabajando hilo %d\n",index );
    vector[i]=rand()%101;
    *sum+=vector[i];
    //printf("Termina hilo %d\n",index );
    pthread_mutex_unlock(&sem);
  }
  pthread_exit(sum);
}


int main(int argc, char const *argv[]) {
  srand(time(NULL));
  if(argc!=2){
    printf("Cantidad erronea de argumentos\n" );
    exit(EXIT_FAILURE);
  }
  int nhilos=atoi(argv[1]);
  pthread_t hilos[nhilos];
  int i, resultado=0;
  int* recibido;
  for(i=0;i<10;i++){
    vector[i]=0;
  }
  for(i=0;i<nhilos;i++){
    pthread_create(&hilos[i],NULL,(void*)generaAleatorios,&i);
    printf("Hilo %d creado\n",i );
    //sleep(1);
  }
  for(i=0;i<nhilos;i++){
    pthread_join(hilos[i],(void**)&recibido);
    resultado+=*recibido;
  }
  printf("Vector: " );
  for(i=0;i<10;i++){
    printf("%d\t",vector[i] );
  }
  pthread_mutex_destroy(&sem);
  printf("\nFINAL=%d\n",resultado );
  return 0;
}
