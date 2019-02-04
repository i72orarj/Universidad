#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
void abrirFirefox(char **argv);
int main(int argc, char **argv)
{
	int i, status;
	pid_t pid;

	for(i=0; i<2; i++)
	{
		pid=fork();
		switch(pid)
		{
			case -1:
					perror("fork error.");
					exit(EXIT_FAILURE);

			case 0:
					if(i==0)
					{
						printf("Soy el hijo %d y mi pid es :%d, mi padre viene siendo %d\n", i,  getpid(), getppid());
						execlp("gnome-calculator", "gnome-calculator", NULL);
						exit(EXIT_SUCCESS);
					}
					if(i==1)
					{
						printf("Soy el hijo %d y mi pid es :%d, mi padre viene siendo %d\n", i,  getpid(), getppid());
						abrirFirefox(&argv[1]);
						exit(EXIT_SUCCESS);
					}		
		}
	}
	while(wait(&status) > 0)
	{
		printf("Esperando hijos...\n");
		exit(EXIT_SUCCESS);
	}

}

void abrirFirefox(char **argv)
{
	execvp(*argv, argv);
}