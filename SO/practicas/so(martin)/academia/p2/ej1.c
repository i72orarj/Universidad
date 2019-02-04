#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
void *imprimir(void * cad);

main()
{
	pthread_t thd1, thd2;
	int error=0;

	char cad1[]="hola";
	char cad2[]="mundo";

	pthread_create(&thd1, NULL, (void *) imprimir, (void *) cad1);
	pthread_create(&thd2, NULL, (void *) imprimir, (void *) cad2);


	pthread_join(thd1, NULL);
	pthread_join(thd2, NULL);

	exit(EXIT_SUCCESS);
} 

void *imprimir(void * cad)
{
	char *cadena_entera= (char *) cad;

	printf("Cadena : %s\n", cadena_entera);
	pthread_exit(NULL);
}