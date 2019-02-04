#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char *argv[]) {

	pid_t childpid = 0;
	int i, n, j, valor, flag;
	n = atoi(argv[1]);

	for (i = 0; i <n; i++){
		childpid = fork();
		if (childpid == -1){

    		printf("ERROR");
    		exit(-1);
   		}else if(childpid == 0){
   		//Estamos en alguno de los hijos

			printf("Proceso ID: %ld padre ID: %ld\n",(long)getpid(), (long)getppid());
			//sleep(40); Descomentando esta linea podremos probar los estados del wait con otra terminal o monitor del sistema
		}else{

				while ((flag = wait(&valor)) > 0)
				{
					if (WIFEXITED(valor)) {
								printf("Soy el padre %d, mi hijo %d termino normal, status=%d\n", getpid(), flag, WEXITSTATUS(valor));
						  } else if (WIFSIGNALED(valor)) {
								printf("Soy el padre %d, mi hijo %d obtuvo senial killed (signal %d)\n", getpid(), flag, WTERMSIG(valor));
						  } else if (WIFSTOPPED(valor)) { //Para cuando se para un proceso. Al usar wait() en vez de waitpid() no nos sirve.
								printf("Soy el padre %d, mi hijo %d  fue parado (signal %d)\n", getpid(), flag, WSTOPSIG(valor));
						  } else if (WIFCONTINUED(valor)) { //Para cuando se para un proceso. Al usar wait() en vez de waitpid() no nos sirve.
						  		printf("Soy el padre %d, mi hijo %d  fue reanudado.\n", getpid(), flag);
						  }
				}				


		}
   
	}

return 0;
}