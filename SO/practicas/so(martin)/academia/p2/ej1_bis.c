#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * imprimir(void * arg);

int main(int argc, char **argv)
{
	
	pthread_t thd1, thd2;
	char *cad1=argv[1];
	char *cad2=argv[2];


	pthread_create(&thd1, NULL, (void *) imprimir, (void *) cad1);
	pthread_create(&thd2, NULL, (void *) imprimir, (void *) cad2);


	pthread_join(thd1, NULL);
	pthread_join(thd2, NULL);

}


void * imprimir(void * arg)
{
	char *cadena= (char *) arg;

	printf("La cadena es: %s\n", cadena);
	pthread_exit(NULL);
}