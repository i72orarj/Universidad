#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
void tratarSennal();
int main()
{
	pid_t pid;

	printf("Mi pid es %d\n", getpid());

	
		signal(SIGUSR1, tratarSennal);
		while(1)
		pause();
	

}

void tratarSennal()
{
	puts("He recibido una senyal.");
}