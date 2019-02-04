#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>



void * contar(void * parametro){

	char *cad[30];

	*cad = (char *)parametro;

	int *tam;

	tam=(int*)malloc(sizeof(int));

	*tam = strlen(*cad);

pthread_exit((void *) tam);
}


void * mul(void * parametro){

	float *n;

	n = (float *)parametro;

	float *mul;

	mul = (float *)malloc(sizeof(float));

	*mul = *n * 0.1;

pthread_exit((void *) mul);
}



int main(){

	pthread_t hebras[2];


	char cad[30];
	float num;

	int *puntero_a_cad;
	float *puntero_a_float;


	printf("Introduce tu cadena: ");
	gets(cad);
	
	printf("\nIntroduce tu numero: ");
	scanf("%f", &num);
	
	pthread_create(&hebras[0], NULL, (void *) contar, (void *) cad);
	
	pthread_join(hebras[0], (void **) &puntero_a_cad);

	pthread_create(&hebras[1], NULL, (void *) mul, (void *) &num);

	pthread_join(hebras[1], (void **) &puntero_a_float);


	printf("\nEl numero de caracteres es: %d\n", *puntero_a_cad);


	printf("La multiplicacion es: %f\n", *puntero_a_float);

return 0;
}

