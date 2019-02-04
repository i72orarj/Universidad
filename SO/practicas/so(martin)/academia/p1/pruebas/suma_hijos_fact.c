#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char **argv)
{
	pid_t pid;
	int i, status, flag, j,k,suma1=0, suma2=1;
	int num1=atoi(argv[1]);
	int num2=atoi(argv[2]);

	for(i=0; i<2;i++)
	{

		pid=fork();
			sleep(1);	

		switch(pid)
		{
			case -1: 
					printf("Error en el fork\n");
					printf("el error ha sido %d\n", errno);
					exit(EXIT_FAILURE);
			case 0:

					if(i==0)
					{
						printf("Soy el hijo %d, mi pid es %d y mi papa es %d\n", i+1, getpid(), getppid());
						for(j=num1; j>0; j--)
						{
							suma1=suma1+j;

						}
						printf("El sumatorio de %d es %d\n", num1, suma1);
						exit(EXIT_SUCCESS);
					}

						if(i==1)
					{
						printf("Soy el hijo %d, mi pid es %d y mi papa es %d\n", i+1, getpid(), getppid());
						for(k=1; k<=num2; k++)
						{
							suma2=suma2*k;

						}
						printf("El factorial de %d es %d\n", num2, suma2);
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