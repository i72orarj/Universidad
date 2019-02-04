#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
int main(int argc, char **argv)
{
	int pid=atoi(argv[1]);
	int cont=0;

	while(cont<=6)
	{
		kill(pid, SIGUSR1);

		cont++;
	}
	if(cont>6)
	kill(pid, SIGINT);
}