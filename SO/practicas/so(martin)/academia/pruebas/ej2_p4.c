#include <stdio.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <semaphore.h>

main()
{
	int *cont=NULL;
	sem_t *mutex=NULL;
	int id1, id2, status, i, j;
	int suma=0;
	key_t clave1, clave2;
	pid_t pid;

	clave1 = ftok(".", 124);
	clave2 = ftok(".", 125);

	id1= shmget(clave1, 1*sizeof(int), IPC_CREAT | 0777);
	id2 = shmget(clave2, 1*sizeof(sem_t), IPC_CREAT | 0777);

	cont=(int*)shmat(id1, NULL, 0);
	mutex= (sem_t*)shmat(id2, NULL, 0);

	*cont =0;
	sem_init(mutex,0,1);

	for(i=0; i<5;i++)
	{
		pid=fork();
		switch(pid)
		{
			case -1:
					perror("fork error");
					printf("errno value:%d, which means : %s\n", errno, strerror(errno));
					exit(EXIT_FAILURE);
			case 0:
					for(j=0; j<100;j++)
					{
						sem_wait(mutex);
						(*cont)++;
						sem_post(mutex);
					}
					exit(EXIT_SUCCESS);

		}
	}
	
	while(wait(&status)>0)
	{
		puts("Esperando a los hijos.");
	}
	
printf("El valor del contador al final del bucle es %d\n", *cont);
	shmdt((char *) cont);
	shmdt((char *) mutex);

	shmctl(id1, IPC_RMID, (struct shmid_ds *) NULL);
	shmctl(id2, IPC_RMID, (struct shmid_ds *) NULL);
}