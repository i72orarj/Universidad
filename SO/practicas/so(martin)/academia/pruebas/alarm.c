#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
void alarma();
main()
{
	int cont=0;

	signal(SIGALRM, alarma);

	alarm(2);
	pause();
	alarm(2);
	pause();

	while(cont<=4)
	{
		alarm(1);
		pause();
		cont++;
	}
	if(cont>5)
	{
		kill(getpid(), SIGKILL);
	}

}

void alarma()
{
	puts("Me cago en todo");
}