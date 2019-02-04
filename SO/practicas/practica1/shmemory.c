#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

#define ITER		5
#define CHILDREN	3
#define TAM 100
// The process finished correctly
#define Ok	7

int main()
{
    int i, shmid, status,sum=0;
    key_t key;
    int *counter;
    void cambia();
    void cambiaAleatorio();
    void sumaVector(int* sum);
    struct shmid_ds buf;

    // Shared memory
    key = ftok("shmemory.c", 1);
    if ((shmid = shmget(key, TAM*sizeof(int), IPC_CREAT | 0777)) == -1)
	   exit(1);

    counter = (int *) shmat(shmid, NULL, 0);

    srand(time(NULL));
    for (i=0;i<TAM;i++){
      *(counter+i)=rand();
    }

    // Run children
    for (i = 0; i < CHILDREN; i++) {
	     if (!fork()) {
          if(i==0){
            cambia();
            exit(0);
          }
          if(i==1){
            cambiaAleatorio();
            exit(0);
          }
          if(i==2){
            sumaVector(&sum);
            printf("suma=%d\n",sum );
            exit(0);
          }
         }
       }


    // Wait to finish
    for (i = 0; i < CHILDREN; i++) {
	   pid_t pid = wait(&status);
	   printf("\nChild %d finished with status %d\n", pid, WEXITSTATUS(status));
   }
    for(i=0;i<TAM;i++){
      printf("%d\n",*(counter+i) );
    }
    // Detach segment
    shmdt(counter);

    // Mark the segment to be destroyed
    shmctl(shmid, IPC_RMID, &buf);

    return 0;
}


void cambia()
{
    int *counter, *aux;
    int indice,valor;
    int i, shmid;
    key_t key;

    // Shared memory
    key = ftok("shmemory.c", 1);
    if ((shmid = shmget(key, TAM*sizeof(int), 0)) == -1)
	     perror("Child: ");
    counter = (int *) shmat(shmid, NULL, 0);

    for (i = 0; i < 10; i++) {
      printf("Indice %d: ",i );
      scanf("%d",&indice );
      printf("Valor %d: ",i );
      scanf("%d",&valor );
      *(counter+indice)=valor;
    }
    shmdt(counter);
    exit(Ok);
}

void cambiaAleatorio()
{
    int *counter;
    int i, shmid,indice;
    key_t key;

    // Shared memory
    key = ftok("shmemory.c", 1);
    if ((shmid = shmget(key, TAM*sizeof(int), 0)) == -1)
	     perror("Child: ");
    counter = (int *) shmat(shmid, NULL, 0);

    for (i = 0; i < 100; i++) {
      indice=rand()%100;
      *(counter+indice)=rand();
    }
    shmdt(counter);
    sleep(1);
    exit(Ok);
}


void sumaVector(int* sum)
{
    int *counter;
    int i, shmid;
    key_t key;

    // Shared memory
    key = ftok("shmemory.c", 1);
    if ((shmid = shmget(key, TAM*sizeof(int), 0)) == -1)
	     perror("Child: ");
    counter = (int *) shmat(shmid, NULL, 0);

    for (i = 0; i < 5; i++) {
	     for(int j=0;j<TAM;j++){
         *sum=*sum+*(counter+j);
       }
    }
    shmdt(counter);
    sleep(30);
    exit(Ok);
}


/*void adder(int id)
{
    double x = 1.0, l;
    double *counter;
    int i, shmid;
    key_t key;

    // Shared memory
    key = ftok("shmemory.c", 1);
    if ((shmid = shmget(key, sizeof(double), 0)) == -1)
	     perror("Child: ");
    counter = (double *) shmat(shmid, NULL, 0);

    for (i = 0; i < ITER; i++) {
	     l = *counter;
	     fprintf(stdout, "Process %d: %lf\n", id, *counter);
	     l += x;
	     *counter = l;
    }
    fprintf(stdout, "*Process %d: %lf\n", id, *counter);
    shmdt(counter);


    exit(Ok);
}*/
