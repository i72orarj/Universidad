//#include <sys/types.h>
//#include <sys/wait.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <semaphore.h>
#include <pthread.h>

#define NHILOS 10

int contador;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void* suma(void* a){
  int i=0;
  //sem_wait(&sem);
  pthread_mutex_lock(&mutex);
  while(i<100){
    contador++;
    i++;
  }
  //printf("%d\n",contador );
  pthread_mutex_unlock(&mutex);
  //sem_post(&sem);
}


int main(int argc, char const *argv[]) {
  int id_memoria,status;
  pthread_t hilos[NHILOS];
  //key_t llave;
  //llave=ftok("ej2.c",1);
  //id_memoria=shmget(llave,sizeof(int),IPC_CREAT|0777);
  //contador=shmat(id_memoria,(char*)0,0);
  contador=0;
  //sem_init(&sem,1,1);
  for(int i=0;i<NHILOS;i++){
    pthread_create(&hilos[i],NULL,suma,NULL);
  }
  for(int i=0;i<NHILOS;i++){
    pthread_join(hilos[i],NULL);
  }

  printf("contador:%d\n",contador );
  //shmdt(contador);
  //shmctl(id_memoria,IPC_RMID,NULL);

  return 0;
}
