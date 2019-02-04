#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

struct parametros
{
	char caracter;
	char cadena[256];
};

void *fcadena(void *arg);
void *contador(void *arg);
int main()
{
	pthread_t thd1, thd2;
	struct parametros p;
	int num;
	int *valor_devuelto1, *valor_devuelto2;

	printf("Introduzca una cadena\n");
	scanf("%s", p.cadena);
	getchar();
	printf("Introduzca un caracter\n");
	scanf("%c", &p.caracter);

	printf("Introduzca un número\n");
	scanf("%d", &num);

	pthread_create(&thd1, NULL, (void *) fcadena, (void *) &p);
	pthread_create(&thd2, NULL, (void *) contador, (void *) &num);


	pthread_join(thd1, (void *) &valor_devuelto1);
	pthread_join(thd2, (void *) &valor_devuelto2);

	printf("La cadena '%s' tiene %d letra/as con el caracter '%c'\n", p.cadena, *valor_devuelto1, p.caracter);

	if(*valor_devuelto2==0)
		printf("El número %d es par\n", num);
	else 
		printf("El numero %d es impar\n", num);
}

void *fcadena(void *arg)
{
	struct parametros *param=(struct parametros *)arg;
	int *cont=malloc(sizeof(int));
	int i;
	*cont=0;
	for(i=0;i<strlen(param->cadena); i++)
	{
		if(param->caracter==param->cadena[i])
			*cont=*cont+1;
	}
	pthread_exit((void **) cont);
}

void *contador(void *arg)
{
	int *num=(int *)arg;
	int *valor=malloc(sizeof(int));

	if(*num %2==0)
		*valor=0;
	else 
		*valor=1;
	pthread_exit((void **) valor);
}