/*Se dice que un proceso está en el estado de zombie en UNIX cuando, habiendo concluido su ejecución, está a la espera de que su padre efectúe un wait() para recoger su código de retorno (valor devuelto al Sistema Operativo). Para ver un proceso zombie, implemente un programa que tenga un hijo que acabe inmediatamente. Deje dormir al padre mediante la función sleep() durante 30 segundos y que luego acabe. Ejecute el programa en segundo plano (usando &) y monitorice los procesos con la orden de la shell ps -a. Verá que en uno de ellos se indica que el proceso está zombie o perdido mientras sigue ejecutándose el programa padre en la función sleep(). Cuando muere el padre, sin haber tomado el código de retorno del hijo, el hijo es automáticamente heredado por el proceso init, que se encarga de "exorcizarlo" y eliminarlo del sistema.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h> 
#include <sys/wait.h>


int main () {

int estadoHijo; /* Estado devuelto por el hijo */
int flag;		/* Variable que recoge el valor devuelto por wait() */

pid_t pid;
   		
   	pid=fork();

   		
     switch(pid)
	  {
			case -1: /* error del fork() */
					perror("fork error");
					printf("errno value= %d\n", errno); 
					exit(EXIT_FAILURE);
       		 
			case 0: /* proceso hijo */
					printf("Soy el proceso hijo: %d\n", getpid());
					exit(33);

    		default: /* padre */
				printf ("Soy el proceso padre: %d. El pid de mi hijo es %d\n",getpid(), pid );
				sleep(30);
				if((flag=wait(&estadoHijo))>0)
				{
					if (WIFEXITED(estadoHijo) != 0){ //Si se termina bien, "estadoHijo" cogerá  el valor devuelto por éste,33..
						printf ("Padre: Mi hijo ha salido. Devuelve %d\n y flag(su PID) es %d\n", WEXITSTATUS(estadoHijo), flag);//devolver variables por pantalla
					} else if (WIFSIGNALED(estadoHijo)) {  //Para seniales como las de finalizar o matar
            			printf("NO ME VAS A MATAR, MI PADRE ES INIT!!!  child killed (signal %d)\n", WTERMSIG(estadoHijo));
					}
					/*No entrará nunca porque wait solo se ejecuta una vez(no hay bucle). wait devuelve -1 cuando hay fallo en su llamada o
					 cuando se llama Y no hay datos en el sistema de algun hijo que haya tenido el padre, en cuyo caso "errno" se pone a ECHILD*/
					if(errno==ECHILD) {
						printf("No hay hijos que esperar\n");	
						printf("Padre durmiendo de nuevo....\n");
						sleep(10);
					}
				}
				else
				{
					printf("Fallo al ejecutar el wait()\n");
				}
		}
		
return 0;

}
