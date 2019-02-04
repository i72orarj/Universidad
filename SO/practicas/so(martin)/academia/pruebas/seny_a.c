#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
void sennal();
int main()
{

	printf("El pid de este proceso es %d\n", getpid());
	while(1)
	{
		signal(SIGUSR1, sennal);
		
	}

}

void sennal()
{
	puts("Received signal.");
}