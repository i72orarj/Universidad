#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
int main()
{
	pid_t pid;
	int i, status, suma=0;
	float media;

	pid=fork();
	srand(time(NULL));
	switch(pid)
	{
		case -1:
			perror("fork error");
			printf("errno value %d\n", errno);
			exit(EXIT_FAILURE);
			break;
		case 0:
			printf("Soy el hijo : %d y mi padre es :%d\n", getpid(), getppid());
			puts("Introduzca 5 números:");
			for(i=0;i<=5;i++){
				suma=suma+(rand()%10);
		

			}
			media=(float)suma/5;
			printf("La media es: %f\n", media);
			exit(EXIT_SUCCESS);
			break;
		
		default:
			printf("Soy el padre, mi pid es:%d\n", getppid());	

	}
	wait(&status);

	return 0;
}

