#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int i, j, status, n_hijos=2, suma=1;
	int num= atoi(argv[1]);
	pid_t pid;

	for(i=0; i<n_hijos; i++)
	{
		pid=fork();
		switch(pid)
		{
			case -1:
					perror("fork error.");
					printf("errno value %d\n", errno);
					exit(EXIT_FAILURE);

			case 0:
					sleep(2);
					if(i==0)
					{
						
						for(j=1; j<=num; j++)
						{
							suma=suma*j;

						}
						
						printf("Soy el hijo %d , mi pid es %d, mi padre es %d\n", i+1, getpid(), getppid());
						printf("el factorial de %d es %d\n", num, suma);
						
					}
					if(i==1)
					{

						printf("Soy el hijo %d , mi pid es %d, mi padre es %d\n", i+1, getpid(), getppid());
						execlp("ls", "ls", NULL);
						
					}	
					exit(EXIT_SUCCESS);	
		}
		printf("Soy la main y mi pid es %d\n", getpid());
		 if (WIFEXITED(status)) {
            printf("child exited, status=%d\n", WEXITSTATUS(status));


        } else if (WIFSIGNALED(status)) {
            printf("child killed (signal %d)\n", WTERMSIG(status));


        } else if (WIFSTOPPED(status)) {
            printf("child stopped (signal %d)\n", WSTOPSIG(status));

        }
	}
}