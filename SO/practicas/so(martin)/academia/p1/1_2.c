#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
int main(int argc, char **argv)
{
	pid_t pid;
	int i, n, status;
	n=atoi(argv[1]);
	pid=fork();
	switch(pid)
	{
		case -1:
			perror("fork error");
			printf("errno value %d\n", errno);
			exit(EXIT_FAILURE);
			break;
		case 0:
			for(i=0;i<n;i++)
			{
				pid=fork();
				printf("Soy el proceso hijo %d y mi pid es:%d\n", i, getpid());
				exit(EXIT_SUCCESS);
			}

		
		
		default:
			printf("Soy el padre, mi pid es:%d\n", getppid());	

	}
	wait(&status);

	return 0;
	}
