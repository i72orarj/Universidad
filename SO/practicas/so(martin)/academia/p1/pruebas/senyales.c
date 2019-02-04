#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
void hacerLs();
main()
{
	
	int cont=0;
	signal(SIGUSR1, hacerLs);
		
	

		while(cont<=4)
	{
		kill(getpid(), SIGUSR1);
		sleep(1);
		cont++;
	}
	
	

	kill(getpid(), SIGKILL);

}

void hacerLs()
{
	system("clear");
}