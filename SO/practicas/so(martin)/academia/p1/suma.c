#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


/*
Ejercicio muy importane de cara al examen, puede ser fijada como plantilla
*/



int main(int argc, char **argv)
{
	int status, i, j, k, n1, n2, suma1=1, suma2=0, sumatot=0;
	pid_t pid;
			if(argc!=3)
			{
				puts("error al introducir los argumentos.");
				exit(0);
			}

	n1=atoi(argv[1]);
	n2=atoi(argv[2]);
	for(i=0;i<2;i++)
	{
		pid=fork();
	
			switch(pid)
			{
				case -1:
				perror("\n fork error");
				printf("\nerrno value = %i.\n", errno);
				exit(EXIT_FAILURE);
				break;

				case 0:
					if(i==0) //Diferenciamos los procesos en dos i==0 e i==1
					{
						printf("Soy el primer hijo mi pid es %d, y mi padre es %d\n", getpid(), getppid());
						for(j=1;j<=n1;j++){
							suma1=suma1*j;
							
										}
										exit(suma1);
						
					}
					
					
					else if(i==1)
					{
						printf("Soy el segundo hijo mi pid es %d\n", getpid());
						for(k=0;k<=n2;k++){
							suma2=suma2+k;
							
										}
										exit(suma2);		
						
					}

					
					
					break;

			}
	}	
		while( wait(&status) > 0 )
		{
			sumatot+=WEXITSTATUS(status); //Siempre poner esta macro, muy importante
			


		}
		printf("La suma total es %d\n", sumatot);

}