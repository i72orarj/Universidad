#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


int main()
{
	int status, flag, i;
	pid_t pid;

	FILE *fich=NULL;
	fich=fopen("salida.txt", "w");
	for(i=0;i<2;i++)
	{
		pid=fork();
		switch(pid)
		{
			case -1:
					perror("fork error");
					printf("errno valune %d\n", errno);
					exit(EXIT_FAILURE);
					break;
			case 0:
			if(i==0){


					printf("Hijo %d con pid:%d, mi papa es %d\n", i, getpid(), getppid());		
					fprintf(fich,"+++++\n");
					exit(EXIT_SUCCESS);
					
					}
			if(i==1)
			{

					printf("Hijo %d con pid:%d, mi papa es %d\n", i, getpid(), getppid());		
					fprintf(fich,"-----\n");
					exit(EXIT_SUCCESS);
			}		
			break;


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
	fprintf(fich,"*****\n");
	

	fclose(fich);
}