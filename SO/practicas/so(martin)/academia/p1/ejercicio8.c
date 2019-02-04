#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
void tratarSennal();
main()
{
	pid_t pid;
	int cont=0;

	pid=fork();

	if(pid==-1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	 if(pid==0)
	{
		printf("Soy el hijo, mi pid es:%d, mi padre es %d\n", getpid(), getppid());
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
	printf("He recibido una señal de mi padre.\n");
}