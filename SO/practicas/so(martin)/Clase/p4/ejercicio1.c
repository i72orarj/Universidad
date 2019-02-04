#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define N 3

int main()
{
	int *cont=NULL;
	int id;
	key_t Clave;
	int i, l, status, j;
	pid_t pid;

	Clave = ftok (".", 125);

     if (Clave == -1)
     {
     printf("No consigo clave para Memoria compartida\n");
     exit(0);
     }


     	id= shmget (Clave, sizeof(int)*1, 0777 | IPC_CREAT);
	if (id == -1)
	{
		printf("No consigo Id para Memoria compartida\n");
		exit(0);
	}
	//Mapeo

	cont = (int *)shmat (id, NULL, 0);
	if (cont == NULL)
	{
		printf("No consigo Memoria compartida");
		exit (0);
	}

*cont=0;
	for(i=0;i<N;i++)
	{
		pid=fork();
		switch(pid)
		{
			case -1:
					puts("Error al crear el proceso");
					exit(EXIT_FAILURE);

			case 0:
					printf("Soy el hijo. Mi pid es %d y mi padre es %d\n", getpid(), getppid());
					for(j=0;j<100;j++)
					{
					l=*cont;
					l++;
					*cont=l;
					usleep (1000);
					}
					exit(EXIT_SUCCESS);


		}

		
	}
	while( wait(&status) >0)
		{
			puts("Soy el padre.");
		}
printf("La variable contadora es %d\n", *cont);

//	Terminada de usar la Memoria compartida, la liberamos.
	//
	shmdt ((char *)cont);
	shmctl (id, IPC_RMID, (struct shmid_ds *)NULL);


}