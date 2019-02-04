#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

/**
 * -------------------------------------
 * Programa creado por Debian@Linceus.es
 * -------------------------------------
 */

//Se crearán dos hijos, el primero abrirá la calculadora y otro abrirá un editor de textos para N ficheros


int main(int argc, char * argv[]) {
	pid_t pid;
	int i;
	int flag;
	int valor;
	
	//Si el número de argumentos es menor a tres no se lanzará nada por error en los parámetros
if(argc > 3) {
		
//Se crean los dos hijos
	for(i=0; i<2; i++) {
		pid=fork();
		if(pid == -1) {
			exit(EXIT_FAILURE);
		}
		else if(pid == 0) { //Si es el hijo, el programa diferenciará entre el primer hijo y el segundo
			if(i==0) {
				hijoCalculadora(argv[1]); //Si es el primero abre la calculadora
			}
			else {
				hijoGedit(&argv[2]); //Si es el segundo abrirá gedit, pasandole para ello el resto de parámetros
				//como un array 
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
	
}
else {
	printf("No has puesto el número de argumentos correctos");
}
	return 0;
}


//La llamada a los dos programas que se abrirán se hará mediante el uso de funciones.

//La primera es bastante simple, le pasaremos simplemente el primer argumento de la llamada al programa como comando.

int hijoCalculadora(char * comando) {
	
	execlp(comando, comando, NULL);
	return 0;
}


//El segundo es un poco más "especial", como le estamos pasando los argumentos como un array recibirá un char **
int hijoGedit(char ** argv) {
	
	//Con execvp podemos utilizar un array para la invocación del comando, así que le pasamos el texto tal cual y el array de parámetros
	execvp(*argv, argv);
	
	return 0;
}
