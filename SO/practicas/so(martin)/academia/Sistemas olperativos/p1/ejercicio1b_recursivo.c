#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <errno.h>
#include <stdlib.h>

void crearHijo(int n)
{
	int valor,flag;
	pid_t rf;
	rf = fork();		

	switch (rf) 
	{ 
		case -1: 
			perror("fork error"); 
			printf("errno value= %d\n", errno); 
			exit(EXIT_FAILURE);

		case 0: 
			printf ("Soy %d y mi padre es %d\n", getpid( ), getppid());
			if(n>0)
			{
				crearHijo(n-1);
			}			
			break; 

		 default: 
			while ((flag = wait(&valor)) > 0)
			{
				if (WIFEXITED(valor)) {
							printf("Soy el padre %d, mi hijo %d termino normal, status=%d\n", getpid(), flag, WEXITSTATUS(valor));
					  } else if (WIFSIGNALED(valor)) {
							printf("Soy el padre %d, mi hijo %d obtuvo senial killed (signal %d)\n", getpid(), flag, WTERMSIG(valor));
					  } else if (WIFSTOPPED(valor)) { //Para cuando se para un proceso. Al usar wait() en vez de waitpid() no nos sirve.
							printf("Soy el padre %d, mi hijo %d  fue parado (signal %d)\n", getpid(), flag, WSTOPSIG(valor));
					  } else if (WIFCONTINUED(valor)) { //Para cuando se para un proceso. Al usar wait() en vez de waitpid() no nos sirve.
					  		printf("Soy el padre %d, mi hijo %d  fue reanudado.\n", getpid(), flag);
					  }
			}	 
	}
}

int main(int argc, char *argv[])
{ 
	int n;

	if(argc==2) 
	{
		n = atoi(argv[1])-1;
	}
	else
	{
	  /* check for valid number of command-line arguments */
	  printf("Usage: %s processes\n", argv[0]);
	  exit(EXIT_FAILURE);
	}

	crearHijo(n);
 
	printf ("\nFinal de ejecucion de %d \n", getpid()); 
}
