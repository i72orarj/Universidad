#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

#define CHILDREN	3
#define TAM 100
#define Ok	7

void ph1(int *v){
   int indice, valor;
   size_t i;
   for(i=0;i<10;i++){
     printf("Indice: ");
     scanf("%d",&indice);
     printf("Valor: ");
     scanf("%d",&valor);
     v[indice]=valor;
   }
  exit(Ok);
 }

void ph2(int *v){
  size_t i;
  for(i=0;i<TAM;i++){
    v[rand()%TAM]=rand();
    sleep(1);
  }
  exit(Ok);
}

void ph3(int *v){
  size_t i;
  size_t j;
  int sum=0;
  for(i=0;i<5;i++){
    for(j=0;j<TAM;j++){
      sum=sum+v[j];
    }
    printf("La suma de los elementos es %d\n",sum);
    sleep(30);
  }
  exit(Ok);
}

int main(){
    srand(time(NULL));
    int i, shmid, status;
    key_t key;
    int *v;
    struct shmid_ds buf;

    key = ftok("practica1.c", 1);
    if ((shmid = shmget(key,TAM*sizeof(int), IPC_CREAT | 0777)) == -1)
	   exit(1);

    v = (int *) shmat(shmid, NULL, 0);
    //*v = 0.0;

    for (i = 0; i < CHILDREN; i++){
	     if (!fork()){
         if(i==0){
           ph1(v);
         }
         else if(i==1){
           ph2(v);
         }
         else if(i==2){
           ph3(v);
         }
	        exit(0);
	     }
    }

    for (i = 0; i < CHILDREN; i++){
	     pid_t pid = wait(&status);
	     printf("\nChild %d finished with status %d\n", pid, WEXITSTATUS(status));
    }

    // Detach segment
    shmdt(v);

    // Mark the segment to be destroyed
    shmctl(shmid, IPC_RMID, &buf);

    return 0;
}
