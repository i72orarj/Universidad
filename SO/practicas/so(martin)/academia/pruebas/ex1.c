#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
	pid_t pid;
	int status, flag;
	int i, j, suma=1;
	int num=atoi(argv[1]);
	int op=atoi(argv[2]);

	if(argc!=3)
	{
		puts("Error en la línea de órdenes.");
		exit(EXIT_FAILURE);
	}


	for(i=0; i<2; i++)
	{
		sleep(2);
		pid=fork();

		switch(pid)
		{
			case -1:
						perror("fork error");
						exit(EXIT_FAILURE);
			case 0:
					if(i==0)
					{
						printf("Soy el hijo %d , mi pid es %d y mi padre es %d\n", i, getpid(), getppid());
						for(j=1; j<=num; j++)
							suma=suma*j;
						printf("El factorial de %d es %d\n", num, suma);
						exit(EXIT_SUCCESS);
					}			
					if(i==1)
					{
						printf("Soy el hijo %d , mi pid es %d y mi padre es %d\n", i, getpid(), getppid());
						if(op==0)
						execl("/bin/ls", "ls -l", NULL);
						if(op==1)
						execlp("gnome-calculator", "gnome-calculator", NULL);
						exit(EXIT_SUCCESS);	
					}

		}
	}
	if (WIFEXITED(status)) {
            printf("child exited, status=%d\n", WEXITSTATUS(status));


        } else if (WIFSIGNALED(status)) {
            printf("child killed (signal %d)\n", WTERMSIG(status));


        } else if (WIFSTOPPED(status)) {
            printf("child stopped (signal %d)\n", WSTOPSIG(status));
        }
}