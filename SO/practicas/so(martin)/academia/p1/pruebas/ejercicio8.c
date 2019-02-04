#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
void Sennal();
main()
{
	pid_t pid;
	int cont =0;

	pid=fork();
	if(pid==-1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}

	if(pid==0)
	{
		printf("Soy el hijo con pid:%d , mi padre es %d\n", getpid(), getppid());
		signal(SIGUSR1, Sennal);
		for(;;);
		pause();
		exit(EXIT_SUCCESS);
	}

	while(cont<=5)
	{
		sleep(1);
		kill(pid, SIGUSR1);
		cont++;
	}
	if(cont>5)
		kill(pid, SIGKILL);
}

void Sennal()
{
	puts("He recibido una senyal.");
}