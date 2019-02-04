#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <semaphore.h>

#define nhilos 10
#define iter 100

void main()
{
	int *cont=NULL;
	int id, id2, i, j, status, flag;
	key_t Clave, Clave2;
	sem_t *mutex=NULL;
	pid_t pid;

	Clave = ftok (".", 125);

     if (Clave == -1)
     {
     printf("No consigo clave para Memoria compartida\n");
     exit(0);
     }

	id=  shmget (Clave, sizeof(int)*1, 0777 | IPC_CREAT);
	if (id == -1)
	{
		printf("No consigo Id para Memoria compartida\n");
		exit(0);
	}

	cont = (int *)shmat (id, NULL, 0);
	if (cont == NULL)
	{
		printf("No consigo Memoria compartida");
		exit (0);
	}

	*cont=0;

	Clave2= ftok(".", 126);
	    if (Clave2 == -1)
     {
     printf("No consigo clave para Memoria compartida\n");
     exit(0);
     }

	id2=  shmget (Clave2, sizeof(sem_t)*1, 0777 | IPC_CREAT);
	if (id2 == -1)
	{
		printf("No consigo Id para Memoria compartida\n");
		exit(0);
	}

	mutex = (sem_t *)shmat (id2, NULL, 0);
	if (mutex == NULL)
	{
		printf("No consigo Memoria compartida");
		exit (0);
	}


	sem_init(mutex,1,1);

	for(i=0;i<nhilos;i++)
	{
		pid=fork();

		switch(pid)
		{
			case -1:
					perror("fork error");
					printf("errno value %d\n", errno);
					exit(EXIT_FAILURE);

			case 0:
					for(j=0;j<iter;j++)
					{
					sem_wait(mutex);
					printf("Soy el hijo y mi pid es %d , mi padre es %d\n", getpid(), getppid());
					(*cont)++;
					sem_post(mutex);
					}

					shmdt ((char *)cont);
					shmdt ((char *)mutex);
					exit(EXIT_SUCCESS);
		}

while ((flag = wait(&status)) > 0)
				{
					if (WIFEXITED(status)) {
				            printf("child exited, status=%d\n", WEXITSTATUS(status));
				        } else if (WIFSIGNALED(status)) {
				            printf("child killed (signal %d)\n", WTERMSIG(status));
				        } else if (WIFSTOPPED(status)) {
				            printf("child stopped (signal %d)\n", WSTOPSIG(status));
						  }
				}
				if (flag==-1 && errno==ECHILD)
					printf("No hay más hijos que esperar\n");
				else
				{
					printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n"); //Si algo
					//interrumpe la ejecución de los hijos saltará este error
					exit(EXIT_FAILURE);
				}

	}

printf("El valor del contador es: %d\n", *cont);

shmctl (id, IPC_RMID, (struct shmid_ds *)NULL);
shmctl (id2, IPC_RMID, (struct shmid_ds *)NULL);

}
