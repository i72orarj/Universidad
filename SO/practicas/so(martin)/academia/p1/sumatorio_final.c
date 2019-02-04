#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void abrirGedit(char **cad);


int main(int argc, char **argv)

{
	int status, flag, i;
	pid_t pid;
	int num_hijos=4;//Son 4 hijos ya que contamos ./ej.exe 3 4 5 gedit ..... en total son 4 argumentos.

	for(i=0;i<num_hijos;i++)
	{
		pid=fork();
		switch(pid)
		{
			case -1:
					perror("fork error");
					printf("errno value %d\n", errno);
					exit(EXIT_FAILURE);
					break;
			case 0:
					if(i<3)
					{

					printf("Hijo %d , con pid:%d , mi papa es %d\n", i, getpid(), getppid() );	
					execlp("./sumatorio.exe", "./sumatorio.exe", argv[i+1], NULL);

					exit(EXIT_SUCCESS);
					}
					else
					{
						abrirGedit(&argv[4]);
						exit(EXIT_SUCCESS);
					}
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

void abrirGedit(char **cad)
{
	execvp(*cad,cad );
}