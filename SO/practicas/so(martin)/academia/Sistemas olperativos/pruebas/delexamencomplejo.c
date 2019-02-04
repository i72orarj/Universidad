#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, char *argv[]){


	int i, flag, valor;

	pid_t hilo;

	for(i=0 ; i<2 ; i++){

		hilo=fork();

		if(hilo==-1){

			printf("ERROR");
			exit(-1);

		}else if(hilo==0){

			if(i==0){

				execlp("./factorial.exe", "./factorial.exe", argv[1], NULL);

			}else{

				execvp("ls",&(argv[2]));

			}

		}


	}


//El padre esperará a sus hijos
	while ((flag = wait(&valor)) > 0)
				{
					if (WIFEXITED(valor)) {
				            printf("child exited, status=%d\n", WEXITSTATUS(valor));
				        } else if (WIFSIGNALED(valor)) {
				            printf("child killed (signal %d)\n", WTERMSIG(valor));
				        } else if (WIFSTOPPED(valor)) {
				            printf("child stopped (signal %d)\n", WSTOPSIG(valor));
						  }
				}
				if (flag==-1 && errno==ECHILD)
					printf("No hay más hijos que esperar\n");
				else
				{
					printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n"); //Si algo
					//interrumpe la ejecución de los hijos saltará este error
					exit(EXIT_FAILURE);
				}









return 0;
}
