#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) 
{
	pid_t pid;
	int i, n, valor, flag;

	if (argc != 2)
	{
	  /* check for valid number of command-line arguments */
	  printf("Usage: %s processes\n", argv[0]);
	  exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]);

	printf("\nProceso %i.\n", getpid());
	for (i=0; i<n; i++)
	{
		pid = fork();
		switch(pid)
		{
			case (-1):
			{
				perror("\nfork error");
				printf("\nerrno value = %i.\n", errno);
				exit(EXIT_FAILURE);
			}
			case (0):
			{
				printf("Proceso hijo %i; padre %i.\n", getpid(), getppid());
				break;
			}
			default:
			{
				while ((flag = wait(&valor)) > 0)
				{
					if (WIFEXITED(valor)) {
								printf("Soy el padre %d, mi hijo %d termino normal, status=%d\n", getpid(), flag, WEXITSTATUS(valor));
						  } else if (WIFSIGNALED(valor)) {
								printf("Soy el padre %d, mi hijo %d obtuvo senial killed (signal %d)\n", getpid(), flag, WTERMSIG(valor));
						  } else if (WIFSTOPPED(valor)) { //Para cuando se para un proceso. Al usar wait() en vez de waitpid() no nos sirve.
								printf("Soy el padre %d, mi hijo %d  fue parado (signal %d)\n", getpid(), flag, WSTOPSIG(valor));
						  } else if (WIFCONTINUED(valor)) { //Para cuando se para un proceso. Al usar wait() en vez de waitpid() no nos sirve.
						  		printf("Soy el padre %d, mi hijo %d  fue reanudado.\n", getpid(), flag);
						  }
				}				
				exit(EXIT_SUCCESS);
			}
		}
	}
	printf("\n");
	return (EXIT_SUCCESS);
}
