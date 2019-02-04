#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
void tratarSennal();
main()
{
	pid_t pid;
	int status, cont=0;
	pid=fork();
	switch(pid)
	{
		case -1:
				printf("Error\n");
				exit(EXIT_FAILURE);
		case 0:
				printf("Soy el hijo mi pid es %d y mi papa es %d\n", getpid(), getppid());
				signal(SIGUSR1, tratarSennal);
				for(;;);
				pause();
				


	}
	while(cont<=5)
	{
		sleep(1);
		kill(pid, SIGUSR1);
	cont++;
	}
	
	
	
		kill(pid, SIGKILL);
	
}

void tratarSennal()
{
	puts("He recibido una señal de mi padre---------------");
}