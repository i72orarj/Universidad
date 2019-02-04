#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
struct param
{
	char caracter;
	char cadena[256];
};
void *caracteres(void *arg);
void *par(void *arg);

int main()
{
	pthread_t thd1, thd2;
	struct param p;
	int num;
	int *valor_devuelto1, *valor_devuelto2;

	printf("Introduzca una cadena\n");
	scanf("%s", p.cadena);
	getchar();
	printf("Introduzca un carcater\n");
	scanf("%c", &p.caracter);
	printf("Introduzca un numero\n");
	scanf("%d", &num);

	pthread_create(&thd1, NULL, (void *) caracteres, (void *) &p);
	pthread_create(&thd2, NULL, (void *) par, (void *) &num);



	pthread_join(thd1, (void **) &valor_devuelto1);
	pthread_join(thd2, (void **) &valor_devuelto2);

	printf("El caracter '%c' aparece %d veces en '%s'\n", p.caracter, *valor_devuelto1, p.cadena);

	if(*valor_devuelto2==0)
	printf("El número %d es par\n", num);
	else 
	printf("El número %d es impar\n", num);
}

void *caracteres(void *arg)
{
	struct param *f=(struct param *)arg;
	int i;
	int *cont=malloc(sizeof(int));
	*cont=0;
	for(i=0; i<strlen(f->cadena); i++)
	{
		if(f->caracter==f->cadena[i])
			(*cont)++;
	}
	pthread_exit((void *) cont);

}

void *par(void *arg)
{
	int *numero=(int *)arg;
	int *par_impar=malloc(sizeof(int));

	if(*numero%2==0)
	{
		*par_impar=0;
	}
	else
		*par_impar=1;
	pthread_exit((void *) par_impar);
}