
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
void funcion();
main(int argc, char **argv)
{
	int cont =0, n=atoi(argv[1]);

	signal(SIGALRM, funcion);

	alarm(5);
	pause();
	alarm(3);
	pause();
	alarm(1);
	pause();

	printf("Empiezan los timbrazos selectivos\n");
	while(cont<=n)
	{
		alarm(1);
		pause();
		cont++;
	}
	if(cont>n)
	{
		kill(getpid(), SIGKILL);
	}
}

void funcion()
{
	printf("RINGGGGG\n");
}