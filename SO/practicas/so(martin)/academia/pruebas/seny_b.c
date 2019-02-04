#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
	int pid=atoi(argv[1]);

	int cont=0;

	while(cont<=5)
	{
		sleep(1);
		kill(pid,SIGUSR1);
		cont++;
	}
	if(cont>6)
		kill(pid,SIGINT);
}