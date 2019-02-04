//Sistemas Operativos
//Práctica 1. Ejercicio 2

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(){
	//Declaración de variables.
	int i;
	int estado_hijo;
	int num_hijos;

	pid_t hijo_pid;

	printf("\n\n");

	printf("Introduzca el número de hijos a crear ..: ");
	scanf("%d", &num_hijos);

	printf("Ejecutando ID ..: %d \n\n", getpid());

	for(i=0;i<num_hijos;i++){
		//Creamos un proceso hijo
		hijo_pid=fork();

		switch (hijo_pid){

			case -1:
				//Error al crear el proceso.
				perror("No se pudo crear un proceso hijo. ");
				printf("Error producido ..: %d\n", errno);
				exit(EXIT_FAILURE);

			case 0:	//Proceso hijo
				//Hijo creado correctamente. Mostramos su id y el del padre.
				printf("         Proceso hijo ID ..: %d  (padre ID ..: %d)\n", getpid(), getppid());
				printf("         (esperando %d segundos para finalizar.)\n\n", (i+1)*10);
				sleep((i+1)*10);
				//Finalizamos el proceso hijo de forma correcta porque ya no tiene que realizar ninguna acción más.
				exit(EXIT_SUCCESS);

			default://Proceso padre
				printf("     --> Se ha creado correctamente el hijo número ..: %d\n\n", i+1);
				break;
		}
	}

	//Una vez que se han lanzado todos los procesos hijos esperamos a que finalicen.

	//waitpid espera a que se produzca un cambio de estado en el proceso hijo que le indiquemos,
	//y lo almacena en estado_hijo.

	// -1 --> le indicamos que controle cualquier hijo
	//WUNTRACED  --> controla si un proceso hijo ha sido parado.
	//WCONTINUED  -> controla si un proceso hijo ha sido reanudado (previamente fue parado).

	hijo_pid=waitpid(-1, &estado_hijo, WUNTRACED | WCONTINUED);
	while( hijo_pid !=-1 ){
		printf("         ( Proceso ..: %d ", hijo_pid);
		//Comprueba el cambio de estado del proceso hijo.

		if (WIFEXITED(estado_hijo)){
			//Finalizó de forma normal. Muestra el valor que retornó.
			printf("   Finalizó y devolvió el valor ..: %d )\n\n",WEXITSTATUS(estado_hijo));
		}else if (WIFSIGNALED(estado_hijo)){
			//Finalizó al recibir una señal no controlada.
			printf("   Finalizó al recibir la señal ..: %d )\n\n", WTERMSIG(estado_hijo));
		}else if (WIFSTOPPED(estado_hijo)){
			//El proceso fue parado.
			printf("   Parado ..: %d )\n\n", WSTOPSIG(estado_hijo));		
		}else if (WIFCONTINUED(estado_hijo)){
			//El proceso fue reanudado.
			printf("   Reanudado. ) \n\n");		
		}
		hijo_pid=waitpid(-1, &estado_hijo, WUNTRACED | WCONTINUED);
	}

	//Comprobamos que se ha finalizado correctamente.
	if(errno==ECHILD){
		//Ya no quedan más hijos por finalizar. Finalización correcta.
		printf ("Fin ejecución ID ..: %d (No quedan más hijos que finalizar.)\n", getpid());
	}
	printf("\n\n");
	return 0;
}

