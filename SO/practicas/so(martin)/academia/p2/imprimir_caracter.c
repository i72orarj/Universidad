#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#define N 10
void *imprimir(void * cad);
main()
{
	int error=0, i;
	pthread_t thd[N];
	char cadena[]="hola mundo";
	


	for(i=0;i<N;i++)
	{

		error=pthread_create(&thd[i], NULL, (void *)imprimir, (void  *) &cadena[i]);
			if(error!=0)
			{
				perror("phtread error.");
				printf("errno value:%d\n", errno);
			}
	}


	for(i=0;i<N;i++)
	{
		pthread_join(thd[i], NULL);
	}
}

void *imprimir(void * cad)
{
	char *caracter= (char *)cad;

	printf("caracter:%c\n", *caracter);
	pthread_exit(NULL);
}