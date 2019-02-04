#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void main()
{
int i, nEle, pid, valor, flag; 				//creamos un contador para controlar los hilos
         
        printf("Introduce el numero de hijos que quieres crear: \n");
	scanf("%d", &nEle);
         
         
        for(i=0 ; i<nEle ; i++)                  //con este bucle crearemos 5 hilos y el padre.
        {
        	pid=fork();
                if(pid==0){						//Creamos el hijo
                
                        printf("\nProceso %d = PID PADRE: %d PID HIJO: %d\n",i, getppid(), getpid());   	//imprimimos en pantalla el pid del hijo el numero de proceso

                }
                else if(pid==-1){
                
                   perror("fork error");
		   printf("errno value= %d\n", errno);  
		   exit(EXIT_FAILURE);
                }else{
        		
        		/*Esperamos a los hijos*/ //En este caso el while solo se ejecutara una vez.
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
				printf("\nNo hay más hijos que esperar por parte del padre %d\n",getpid());
			else
			{
				printf("\nError en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
				exit(EXIT_FAILURE);
			}
			i=nEle;
                }
      }          					
      exit(0);
 }
    
