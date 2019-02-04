#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	pid_t pid;	
	int n,i, status;

	if (argc != 2)
	{
	  /* check for valid number of command-line arguments */
	  printf("Usage: %s processes\n", argv[0]);
	  exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]);
	for (i=1; i<=n; i++){
		pid = fork();
		switch(pid)
		{
			case -1: /* error del fork() */
				perror("fork error");
				printf("errno value= %d\n", errno);
				exit (EXIT_FAILURE);
			case 0: /* proceso hijo */
				printf("Soy un hijo con ID %d y mi padre = %d \n", getpid(), getppid());
				sleep(10*i); //Paramos para que nos de tiempo ver los procesos en otro terminal con "ps -u" o con el monitor del sistema
				exit(EXIT_SUCCESS);
			default: /* padre */ 
				printf("Soy el padre con ID %d; y he creado a mi hijo  %d correctamente\n", getpid(), pid);
		}
	}

	while((pid=wait(&status))!=-1)
   {
	 	if (WIFEXITED(status)) {
            printf("child exited, status=%d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("child killed (signal %d)\n", WTERMSIG(status));
        } else if (WIFSTOPPED(status)) { //Para cuando se reanuda un proceso parado. Al usar wait() en vez de waitpid() no nos sirve.
            printf("child stopped (signal %d)\n", WSTOPSIG(status));
        } else if (WIFCONTINUED(status)){ //Para cuando se reanuda un proceso parado. Al usar wait() en vez de waitpid() no nos sirve.
				printf("child continued\n");		  
		  }
	}
	return (EXIT_SUCCESS);
}
