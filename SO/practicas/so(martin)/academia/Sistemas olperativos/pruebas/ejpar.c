#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


int main(int argc, char *argv[]){


	int num_hilos, i, error, flag, valor;

	pid_t pid;

	num_hilos = argc-1;

	for(i=0 ; i<num_hilos ; i++){

		pid = fork();

		if(pid==-1){

			printf("ERROR\n");
			exit(-1);

		}else if(pid==0){

			error=execlp("./par.exe", "./par.exe", argv[i+1], NULL);
			if(error==-1){

				printf("ERROR\n");

			}
		}




	}



while ((flag = wait(&valor)) > 0)
{
	if (WIFEXITED(valor)) {
            printf("child exited, status=%d\n", WEXITSTATUS(valor));
        } else if (WIFSIGNALED(valor)) {  //Para seniales como las de finalizar o matar
            printf("child killed (signal %d)\n", WTERMSIG(valor));
        } else if (WIFSTOPPED(valor)) { //Para cuando se para un proceso. Al usar wait() en vez de waitpid() no nos sirve.
            printf("child stopped (signal %d)\n", WSTOPSIG(valor));
		  } else if (WIFCONTINUED(valor)){ //Para cuando se reanuda un proceso parado. Al usar wait() en vez de waitpid() no nos sirve.
				printf("child continued\n");		  
		  }
}
if (flag==-1 && errno==ECHILD)
	printf("No hay más hijos que esperar\n");
else
{
	printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
	exit(EXIT_FAILURE);
}







return 0;
}
