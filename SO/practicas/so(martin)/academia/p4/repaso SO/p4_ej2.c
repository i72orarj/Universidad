#include <sys/shm.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

main(int argc, char **argv)
{
	sem_t *mutex;
	int *cont;
	pid_t pid;
	int i, j, status;
	key_t clave1, clave2;
	int id1, id2;
	int n=atoi(argv[1]);

	clave1=ftok(".", 125);
	clave2=ftok(".", 126);

	id1=shmget(clave1, 1*sizeof(int), IPC_CREAT | 0777);
	id2=shmget(clave2, 1*sizeof(sem_t), IPC_CREAT | 0777);

	cont=(int*)shmat(id1, NULL, 0);
	mutex=(sem_t *)shmat(id2, NULL, 0);

	*cont=0;
	sem_init(mutex,0,1);

	for(i=0;i<n;i++)
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
	while(wait(&status) >0)
		{
	printf("Esperando hijos....\n");
		}
	printf("El valor de la cuenta es %d\n", *cont);

	shmdt((char *)cont);
	shmdt((char *) mutex);

	shmctl(id1, IPC_RMID, (struct shmid_ds*)NULL);
	shmctl(id2, IPC_RMID, (struct shmid_ds*)NULL);
}