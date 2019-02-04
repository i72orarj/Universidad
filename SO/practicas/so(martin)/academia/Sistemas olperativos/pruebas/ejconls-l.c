#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

void gedit(char **parametro){

	execvp(*parametro, parametro);

}

void funcionls(char comando[], char extension[]){

	execlp(comando, comando, extension, NULL);

}


int main(int argc, char *argv[]){


	
	pid_t hilo;

	int i, valor, flag;

	for(i=0 ; i<2 ; i++){


		hilo = fork();
		if(hilo==-1){

			printf("ERROR");
			exit(-1);

		}else if(hilo==0){
			
			if(i==0){

				funcionls(argv[1], argv[2]);

			}else{

				gedit(&argv[3]);

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