#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NHILOS 5
#define NELEMENTOS 12

int vector[NELEMENTOS];
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void* cambia(void* a){
  pthread_mutex_lock(&mutex);
  for(int i=0;i<100;i++){
    vector[rand()%NELEMENTOS]++;
  }
  pthread_mutex_unlock(&mutex);
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  pthread_t hilos[NHILOS];
  int i;
  for(i=0;i<NELEMENTOS;i++){
    vector[i]=0;
  }
  for(i=0;i<NHILOS;i++){
    pthread_create(&hilos[i],NULL,cambia,NULL);
  }
  for(i=0;i<NHILOS;i++){
    pthread_join(hilos[i],NULL);
  }
  for(i=0;i<NELEMENTOS;i++){
    printf("%d,\t",vector[i] );
  }
  printf("\n" );
  return 0;
}
