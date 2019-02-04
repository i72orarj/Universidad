#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
void hacerRm(char **arg);
int main(int argc, char **argv)
{
	pid_t pid;
	int i, status;

	for(i=0;i<2;i++)
	{
		pid=fork();

		switch(pid)
		{
			case -1:
					perror("fork error");
					printf("errno value %d\n", errno);
					exit(EXIT_FAILURE);

			case 0:
			
					printf("Soy el hijo y mi padre es %d", getppid());
					if(i==0)
					{
						execlp("ls", "ls", NULL );
						exit(EXIT_SUCCESS);
					}		

					if(i==1)
					{
						hacerRm(&argv[1]);
						exit(EXIT_SUCCESS);
					}

		}
		while(wait(&status) > 0)
		{
			printf("Esperando hijos...\n");
			 if (WIFEXITED(status)) {
            printf("child exited, status=%d\n", WEXITSTATUS(status));


        } else if (WIFSIGNALED(status)) {
            printf("child killed (signal %d)\n", WTERMSIG(status));


        } else if (WIFSTOPPED(status)) {
            printf("child stopped (signal %d)\n", WSTOPSIG(status));
		}
	}
	}

}

void hacerRm(char **arg)
{
	execvp(*arg, arg);
}