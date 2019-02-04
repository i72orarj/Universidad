
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
void funcion();
int main(int  argc, char **argv)
{
	int i, cont=-1, nveces;
	

	nveces=atoi(argv[1]);
	signal(SIGALRM, funcion);
	while(1)
	{
		alarm(1);
		cont++;
		if(cont==nveces)
			kill(getpid(),SIGKILL);
		pause();
	}

}

void funcion()
{
	printf("RING\n");
}