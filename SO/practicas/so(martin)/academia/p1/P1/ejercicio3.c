#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include <errno.h>

int main(int argc,char * argv[])
{
//Declaración de variables.
int i;
int num_hijos;
int estado_hijo;
pid_t hijo_pid;

if(argc<3)
{
	printf("\nSintaxis: %s <número1> <número2> <númeroN>\n\n", argv[0]);
	exit(EXIT_FAILURE);
}

//El primer argumento es el nombre del fichero ejecutable.
num_hijos=argc-1;

printf("Ejecutando ID ..: %d \n\n", getpid());

for(i=0;i<num_hijos;i++)
{
	//Creamos un proceso hijo
	hijo_pid=fork();

	switch (hijo_pid)
	{
		case -1:
			//Error al crear el proceso.
			perror("No se pudo crear un proceso hijo. ");
			printf("Error producido ..: %d\n", errno);
			exit(EXIT_FAILURE);
	
		case 0:	//Proceso hijo
			//Hijo creado correctamente. Mostramos su id y el del padre.
			printf("         Proceso hijo ID ..: %d  (padre ID ..: %d)\n", getpid(), getppid());

			//Calculamos el factorial.Para ejecutar ejecutable creado anteriormente
			if(execlp("./factorial.exe","./factorial.exe",argv[i+1],NULL)==-1)//cada hijo ejecuta un proceso (son 2)
			{
				printf("         Error en la ejecución de ./factorial.exe %s\n", argv[i+1]);//control de errores 
				printf("         Error producido ..: %d\n", errno);
				exit(EXIT_FAILURE);/*sin control de errores= execlp("./factorial.exe","./factorial.exe",argv[i+1],NULL);*/
			}

		default://Proceso padre
			printf("     --> Se ha creado correctamente el hijo número ..: %d\n", i+1);
			break;
	}
}
//Una vez que se han lanzado todos los procesos hijos esperamos a que finalicen.

//waitpid espera a que se produzca un cambio de estado en el proceso hijo que le indiquemos,
//y lo almacena en estado_hijo. Permite a diferencia de wait esperar grupos de procesos, procesos concretos,
//a cualquier proceso, e incluso detectar los cambios de estado de un proceso cuando se para (kill -STOP PID)
//o se reanuda (kill -CONT PID).

// -1 --> Con este parámetro le indicamos que controle la espera de cualquier hijo.
//WUNTRACED  --> controla si un proceso hijo ha sido parado.
//WCONTINUED  -> controla si un proceso hijo ha sido reanudado (previamente fue parado).

hijo_pid=waitpid(-1, &estado_hijo, WUNTRACED | WCONTINUED);

while( hijo_pid !=-1 )
{
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
if(errno==ECHILD)
{
	//Ya no quedan más hijos por finalizar. Finalización correcta.
	printf ("Fin ejecución ID ..: %d (No quedan más hijos que finalizar.)\n", getpid());
}
printf("\n\n");
exit(EXIT_SUCCESS);
}
