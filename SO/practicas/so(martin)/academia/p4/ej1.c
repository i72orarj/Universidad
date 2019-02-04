#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	pid_t pid;
	int n=atoi(argv[1]);
	int *cont=NULL;
	int i, j,  id, status;

	key_t clave;
	clave=ftok(".", 124);

	id= shmget(clave,sizeof(int)*1, IPC_CREAT | 0777);

	cont=(int *) shmat(id, NULL, 0);

*cont=0;
	for(i=0; i<n; i++)
	{
		pid=fork();
		switch(pid)
		{
			case -1:
					perror("fork error");
					exit(EXIT_FAILURE);
			case 0:
					printf("Soy el hijo mi pid es %d y mi papa es %d\n", getpid(), getppid());
					for(j=0; j<100;j++)
					{
						*cont=*cont+1;

					}

					exit(EXIT_SUCCESS);

		}


	}
		while(wait(&status) > 0)
		{
			printf("Esperando a los hijos...\n");


		}
			printf("La suma total es %d\n", *cont);

		shmdt((char *) cont);
		shmctl(id, IPC_RMID, (struct shmid_ds *)NULL);

}
