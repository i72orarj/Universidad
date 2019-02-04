#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

main() {

int i;
int nEle, flag, status;

	printf("Introduce el numero de hijos que quieres crear: \n");
	scanf("%d", &nEle);

	pid_t x; //es el numero de procesos

	for(i=0 ; i<nEle ; i++){
	
		x = fork();  // crea el numero de procesos igual al nEle que hemos introducido.
		
		switch (x){
		
			case -1:
			
				perror("fork error"); //En el caso de que x valga menor que 0 se produciria un error.
				printf("erno value = %d\n", errno);
				break;
				
			case 0:
			
				printf("\nSoy el hijo numero %d, mi pid es %d y mi padre es %d.\n", i, getpid(), getppid()); 
				exit(EXIT_SUCCESS); //nos muestra que hijo es, cual es su pid y quien es su padre.
				break;		
		}
	
	}

	while((flag=wait(&status)) > 0){
	
	
	
	if(flag==-1 && errno==ECHILD){
	
		printf("Salida normal.\n");
		
	}else{
	
		printf("Fallo en wait.\n");
		exit(EXIT_FAILURE);
		}
		}
	
exit(EXIT_SUCCESS);

return 0;
}
