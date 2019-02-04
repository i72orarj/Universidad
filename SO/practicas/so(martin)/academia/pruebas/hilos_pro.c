#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

struct params
{
	char caracter;
	char cadena[512];
};
void *estructura(void *arg);

void *par_impar(void *arg);
main()
{
	pthread_t thd1, thd2;
	int *valor_devuelto1, *valor_devuelto2;
	struct params p;
	int num;

	printf("Introduzca una cadena:\n");
	scanf("%s", p.cadena);
	getchar();
	printf("Introduzca un caracter\n");
	scanf("%c", &p.caracter);

	puts("introduzca un número");
	scanf("%d", &num); 

	pthread_create(&thd1, NULL, (void *) estructura, (void *) &p);
	pthread_create(&thd1, NULL, (void *) par_impar, (void *) &num);

	pthread_join(thd1, (void **) &valor_devuelto1);
	pthread_join(thd2, (void **) &valor_devuelto2);

	printf("El número de veces que aparece '%c' en la cadena '%s' es %d\n", p.caracter, p.cadena, *valor_devuelto1);

	if(*valor_devuelto2==0)
	{
		printf("El número %d es par\n", num);
	}
	else
		printf("El número %d es impar\n", num);

}

void *estructura(void *arg)
{
	struct params *misco=(struct params*)arg;
	int *cont=malloc(sizeof(int));
	int i;

	*cont=0;
	for(i=0; i<strlen(misco->cadena); i++)
	{
		if(misco->caracter== misco->cadena[i])
			(*cont)++;
	}
	pthread_exit((void *) cont);
}

void *par_impar(void *arg)
{
	int *numero=(int *)arg;
	int *devuelto=malloc(sizeof(int));

	if(*numero % 2 ==0)
	{
		*devuelto=0;
	}
	else
		*devuelto=1;
	pthread_exit((void *) devuelto);
}