//  ./a.out parimpar.exe 2 5 3,     luego un 1 con execlp y ejecutar ls -s -t y el 2 con execl

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, char *argv[]){


	pthread_t hilos;

	int i, valor, flag; //n

	
	for(i=0 ; i<2 ; i++){

		hilos=fork();

		if(hilos==-1){

			printf("ERROR");
			exit(-1);
	
		}else if(hilos==0){

			if(i==0){

				execlp("./par.exe", "./par.exe", argv[i+1], NULL);

			}else{

				if(atoi(argv[2])==1)
				{
					//n=argc-algo
					//for(i=0; i<n; i++)
					execlp("ls", "ls", "-t", NULL);
				}
				else if(atoi(argv[2])==2)
				{
	
				}
				
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
