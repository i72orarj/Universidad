#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include <errno.h>



int main(int argc, char *argv[]){

	int num, fac=1, flag, i, status;

	num = atoi(argv[1]);

	pid_t pid;

	pid = fork();

	if(pid==-1){

		printf("ERROR\n");
		exit(-1);

	}else if(pid==0){

		for(i=num ; i>0 ; i--){

			fac = i * fac;
			sleep(1);

		}
		
		printf("El factorial de %d es: %d\n", num, fac);
		exit(0);
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
	





return 0;
}
