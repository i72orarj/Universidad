#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	pid_t pid;
	int n, status, i;
	n=atoi(argv[1]);
		for(i=0;i<n;i++)
		{
			pid=fork();

		}
			if(pid==0)
			{
				printf("Soy el hijo y mi pid es:%d\n", getpid());
				exit(EXIT_SUCCESS);

			}

			wait(&status);
			return 0;
}
