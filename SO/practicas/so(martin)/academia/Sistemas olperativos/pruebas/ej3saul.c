#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void ls(char **cad){


	execvp(*cad, cad);
}

int main(int argc, char *argv[]){

	pthread_t hilos;

	int i;
	int flag, valor;


	
	for(i=0 ; i<2 ; i++){

		hilos=fork();

		if(hilos==-1){

			printf("ERROR");
			exit(-1);

		}else if(hilos==0){

			if(i==0){

					execlp("./suma.exe", "./suma.exe", argv[1], NULL);
			}else{

				//ls(&argv[2]); //con funa funcion por referencia
				//execvp("ls", &argv[2]); //sin escribir ls en argumento y poniendo -s -t
				execvp(argv[2], &argv[2]); //escribiendo en la terminal ls -s -t

			}
		exit(0);
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

return 0;
}
