#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include<signal.h>
void timbraso();
main()
{
	int cont=0;

	signal(SIGALRM, timbraso);
	alarm(5);
	pause();
	alarm(3);
	pause();
	alarm(1);
	pause();

	while(cont<=4)
	{
		alarm(1);
		pause();
		cont++;
	}
	if(cont>=4)
		kill(getpid(), SIGKILL);


}

void timbraso()
{
	puts("RINGGGGGGGG");
}