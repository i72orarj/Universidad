#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

struct parametros
{
	 char cadena[50];
	 char caracter;
};
void * caracteres(struct parametros *p);
void * par_impar(void *arg);



void main()
{
	pthread_t thd1, thd2;
	int error, num, *valor_devuelto1, *valor_devuelto2;
	struct parametros p;
	
	printf("Introduzca una cadena y un caracter\n");
	scanf("%s", p.cadena);
	getchar();
	printf("Introduzca un caracter\n");
	scanf("%c", &p.caracter);

	
	
	pthread_create(&thd1, NULL, (void *) caracteres, (void *) &p);
	
	printf("Introduzca un numero\n");
	scanf("%d", &num);

	pthread_create(&thd2, NULL, (void *) par_impar, (void *) &num);
/*
	printf("El id de la hebra 1 es :%d\n", pthread_self());
	printf("El id de la hebra 2 es :%d\n", pthread_self());
*/

	pthread_join(thd1, (void **) &valor_devuelto1);
	pthread_join(thd2, (void **) &valor_devuelto2);

	printf("El numero de veces que aparece %c es %d\n", p.caracter, *valor_devuelto1 );
	printf("Value : %d\n", *valor_devuelto2);
	if(*valor_devuelto2== 0)
		printf("El número %d es par\n", num);
		if(*valor_devuelto2== 1)
		printf("El número %d es impar\n", num);
	




}

void * caracteres(struct parametros *p)
{
	int i;
	int *cont= malloc(sizeof(int)); 
	*cont =0;

	for(i=0; i<strlen(p->cadena); i++)
	{
		if(p->caracter==p->cadena[i])
			*cont=*cont+1;
	}
	pthread_exit((void *) cont);
}

void * par_impar(void *arg)
{
	int *numero=(int *)arg;
	int *par=malloc(sizeof(int));
	int *impar=malloc(sizeof(int));	

	if(*numero %2 == 0)
	{
		*par=0;
		pthread_exit((void *)par);
	}

		if(*numero %2 != 0)
	{
		*impar=1;
		pthread_exit((void *) impar);
	}
}