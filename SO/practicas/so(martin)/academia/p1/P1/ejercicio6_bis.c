#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


int main(int argc,char * argv[])
{

	if (argc > 4)
	{
		pid_t pid;
		int estado,i;

		for (i = 0; i < 2; ++i)
		{
			pid = fork();

			if(pid == -1)
			{
				perror("fallo en el fork");
				printf("error value= %d\n",errno);
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				if(i == 0)
				{
					execlp(argv[1],argv[1],(char *)0);
					exit(0);
				}
				if(i == 1)
				{
					//la funcion "execvp()" el segundo parametro contiene tanto el titulo como todos los argumentos
					execvp(argv[2],&(argv[2]));
					exit(0);
				}
			}
		}
		while((pid=wait(&estado)) > 0)
		{
			if(WIFEXITED(estado))
			{
				printf("child exited, status=%d\n", WEXITSTATUS(estado));
			}
			else if (WIFSIGNALED(estado))
			{
				printf("child killed (signal %d)\n", WTERMSIG(estado));
			}
			else if (WIFSTOPPED(estado))
			{
				printf("child stoped (signal %d)\n", WSTOPSIG(estado));
			}
		}
	}
	else
	{
		printf("Numero de argumentos invalido:(minimo 4)\n");
		printf("\t-argv[0]->Titulo del programa\n");
		printf("\t-argv[1]->gnome-calculator\n");
		printf("\t-argv[2]->gedit\n");
		printf("\t-argv[3]->fichero1.txt\n");
	}
	return (0);
}
