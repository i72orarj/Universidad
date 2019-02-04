#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <semaphore.h>
#define N 5

main()
{
	sem_t *mutex=NULL;
	int *cont=NULL;
	pid_t pid;
	int i, j, status, id1, id2;
	key_t clave1, clave2;


	
	clave1=ftok(".", 124);
	clave2=ftok(".", 125);

	id1=shmget(clave1, 1*sizeof(int), IPC_CREAT | 0777);
	id2=shmget(clave2, 1*sizeof(sem_t), IPC_CREAT | 0777);

	cont=(int *)shmat(id1, NULL,0);
	mutex=(sem_t *)shmat(id2, NULL,0);
sem_init(mutex, 0, 1);
*cont=0;
	for(i=0;i< N; i++)
	{
		pid=fork();

		switch(pid)
		{
			case -1:
					perror("fork error");
					exit(EXIT_FAILURE);

			case 0:
					printf("Soy el hijo %d: pid %d, mi padre es %d\n", i, getpid(), getppid());
					for(j=0;j<100;j++)
					{
						sem_wait(mutex);
						*cont=*cont+1;
						sem_post(mutex);
					}
					exit(EXIT_SUCCESS);		
		}
	}
	while(wait(&status) > 0)
	{
		puts("Esperando a los hijos\n");
	}
	printf("El contador final es %d\n", *cont);
	
	shmdt((char *) cont);
	shmdt((char *) mutex);

	shmctl(id1, IPC_RMID, (struct shmid_ds *) NULL);

	shmctl(id2, IPC_RMID, (struct shmid_ds *) NULL);
}