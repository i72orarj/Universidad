#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
void funcion(char comando[], char extension[]);
int main(int argc, char **argv)
{
	FILE *fich=NULL;
	pid_t pid;
	char *cad=argv[1];
	int status, i;
	if(argc!=4)
	{
		perror("argument error");
		exit(EXIT_FAILURE);
	}

	fich=fopen(cad, "w+");

	for(i=0; i<3; i++)
	{
		sleep(1);
		pid=fork();
		switch(pid)
		{
			case -1:
					perror("fork error");
					exit(EXIT_FAILURE);
			case 0:
					if(i==0)
					{
						printf("Soy el %d hijo y mi pid es %d, mi padre es %d\n", i, getpid(), getppid());
						fprintf(fich,"+++++++++++Esta escribiendo el primer hijo++++++++++\n");
						exit(EXIT_SUCCESS);
					}
					if(i==1)
					{
						printf("Soy el %d hijo y mi pid es %d, mi padre es %d\n", i, getpid(), getppid());
						fprintf(fich,"-----------Esta escribiendo el segundo hijo----------\n");
						exit(EXIT_SUCCESS);
					}
					if(i==2)
					{
						printf("Soy el %d hijo y mi pid es %d, mi padre es %d\n", i, getpid(), getppid());
						funcion(argv[2], argv[3]);
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
        fprintf(fich,"**********Soy el padre*********\n");
        fclose(fich);
kill(getpid(), SIGINT);


}
void funcion(char comando[], char extension[])
{
	execlp(comando, comando, extension, NULL);
	
}