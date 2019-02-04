#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


int main(int argc, char *argv[]){

	pid_t pid;

	int num, flag, valor, i, suma=0, j, tam;

	tam = argc-1;
	

	

	for(j=0 ; j<tam ; j++){

		pid = fork();
		if(pid==-1){

			printf("ERROR");
			exit(-1);

		}else if(pid==0){
			
			num = atoi(argv[j+1]);
			for(i=0 ; i<=num ; i++){

				suma = suma + i;

			}
		
		printf("La suma de %d vale: %d\n", atoi(argv[j+1]), suma);
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
