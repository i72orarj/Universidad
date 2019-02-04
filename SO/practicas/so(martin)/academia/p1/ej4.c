#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void hijoCalculadora(char *comando);
void hijoGedit(char **argv);

int main(int argc, char **argv)
{
	int  status, i, flag;
	pid_t pid;

		for(i=0;i<2;i++)
		{
			pid=fork();
				switch(pid)
				{
					case -1:
					perror("\nfork error");
					printf("errno value=%d\n", errno);
					exit(EXIT_FAILURE);
					break;

					case 0:
						if(i==0)
						{
							hijoCalculadora(argv[1]);
						}
						else if(i==1)
						{
							hijoGedit(&argv[2]);
						}
						break;

			}

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


void hijoCalculadora(char *comando)
{
	execlp(comando,comando,NULL);
}

void hijoGedit(char **argv)
{
	execvp(*argv, argv);
}
