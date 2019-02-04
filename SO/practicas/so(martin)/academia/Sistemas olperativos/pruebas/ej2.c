#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>



int main(int argc, char *argv[]){


	pid_t pib;
	int tam, i, valor, flag;


	tam = atoi(argv[1]);

	for(i=1 ; i<=tam ; i++){

		pib = fork();

		if(pib==-1){

			printf("\n¡ERROR!");
			exit(0);

		}else if(pib==0){

			printf("Mi pid es %d y el de mi padre es %d\n", getpid(), getppid());


		}else{

			printf("He creado el hijo %d\n", pib);


		}
	}

//espera de finalizacion de procesos
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
if (flag==-1)
	printf("No hay más hijos que esperar\n");
else
{
	printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
	exit(EXIT_FAILURE);
}









return 0;
}
