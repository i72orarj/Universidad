#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int status, flag, nhijos, i;
	pid_t pid;

	nhijos=argc-1;

	for(i=0;i<nhijos;i++)
	{
		pid=fork();
		switch(pid)
		{
			case -1:
					perror("fork error");
					printf("errno value:%d\n", errno);
					exit(EXIT_FAILURE);
					break;
			case 0:
					printf("Hijo %d, id:%d", i, getpid());
					execlp("./factorial.exe", "./factorial.exe", argv[i+1], NULL);
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

}