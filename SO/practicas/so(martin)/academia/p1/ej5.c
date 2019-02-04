#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	pid_t pid;
	int status, i, flag;

	if(argc!=2)
	{
		puts("Argument failure.");
		exit(-1);
	}
	FILE *fich=NULL;
	char *cad=argv[1];
	fich=fopen(cad,"w+");
	


	pid=fork();
		for(i=0;i<5;i++){
				

		switch(pid)
		{
			case -1:
					perror("fork error\n");
					printf("errno value:%d\n", errno);
					break;
			case 0:
					printf("child:%d ,child id:%d, my father's id:%d\n", i, getpid(), getppid());
					fprintf(fich,"--------\n");
					break;

		}
	}
	sleep(1);
			//El padre esperará a sus hijos
	while ((flag = wait(&status)) > 0)
				{
					if (WIFEXITED(status)) {
				            printf("child exited, status=%d\n", WEXITSTATUS(status));
				        } else if (WIFSIGNALED(status)) {
				            printf("child killed (signal %d)\n", WTERMSIG(status));
				        } else if (WIFSTOPPED(status)) {
				            printf("child stopped (signal %d)\n", WSTOPSIG(status));
						  }

		fprintf(fich,"+++++++++\n");
		fclose(fich);

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