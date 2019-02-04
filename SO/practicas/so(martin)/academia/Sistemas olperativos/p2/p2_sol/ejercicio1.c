//Sistemas Operativos
//Práctica 2. Ejercicio 1
//Programa que crea dos hebras para imprimir dos cadenas, cada hebra imprime una cadena.
// --> cadena1 'Hola'
// --> cadena2 'mundo'
// --> O bien las dos cadenas que se reciban por parámetro.


#include <stdio.h>
#include <pthread.h>	//libreria de hilos o hebras, para compilar esta libreria al final -lpthread
#include <errno.h>	//Códigos de error
#include <string.h>	//Cadenas
#include <stdlib.h>
#define TAM 50


void * imprime_cadena(void * parametro) //el tipo void * es por que no sabemos de que tipo es el valor que se le pasa
{
	//Función que imprime la cadena que recibe por parámetro.
	//Declaración de variables.
	char *cadena;
	int i;

	//Conversión de void * a char *
	cadena = (char *)parametro; //hacemos un casting con el tipo que no sabemos de que tipo es

	for(i=0;i<strlen(cadena);i++)
	{
		printf("%c\n", cadena[i]);
		sleep(1);
	}

	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL); //si devuelve una variable, el join tendra una variable que devuelva
}


int main(int argc, char **argv)
{
	//Declaración de variables. 	
	int i;
	int error;
   	char cadenas[2][30];
	pthread_t hebras[2]; //tipo de datos para hebras o hilos "pthread_t"

	//Controlamos los parámetros.
	if(argc==2 || argc>3)
	{
		printf("Parámetros incorrectos.\n");
		printf("Sintaxis correcta: %s <cadena1> <cadena2>\n", argv[0]);
		printf("Se para la ejecución del programa.\n");
		exit(-1);
	}

	if(argc==3)
	{
		//Se reciben las dos cadenas por parámetro.
		strcpy(cadenas[0],argv[1]);
		strcpy(cadenas[1],argv[2]);
	}
	
	//Creamos las hebras.
	for(i=0;i<2;i++)
	{
		error = pthread_create( &(hebras[i]), NULL, (void *) imprime_cadena, (void *) cadenas[i]);
		/* 
		para comprobacion de error hacemos un if(error!=0){fallo exit(-1);}
		crear hebras
		se pone despues siempre NULL
		para cada uno lo crea para eso tenemos el for
		despues (void *) y despues la funcion el hilo llama a esa funcion
		el ultimo argumento es el dato que recibe el hilo, si no recibe nada en este ultimo pondremos NULL

		*/

		//Capturamos los errores que se pueden producir al crear una hebra. Vienen definidos en OpenGroup
		switch (error)
		{
			case 0: //Correcto.
				printf("    (Hilo ppal.) Se ha creado la hebra ..: %lu\n", (unsigned long int)hebras[i]);
				break;
			case EAGAIN: //El sistema no puede crear más hebras bien porque se ha llegado al máximo PTHREAD_THREADS_MAX
				          //o bien porque se ha quedado sin recursos para ello.
				printf("    (Hilo ppal.) Se produjo el error EAGAIN (sin recursos o máximo de hebras alcanzado).\n");
				break;
			case EINVAL: //La configuración especificada en el parámetro attr no es correcta.
				printf("    (Hilo ppal.) Se produjo el error EINVAL (valores de attr incorrectos).\n");
				break;
			case EPERM:  //El proceso no tiene los permisos apropiados para configurar la política de planificacion
				          //o la configuración indicada en el parámetro attr.
				printf("    (Hilo ppal.) Se produjo el error EPERM (sin privilegios para configurar la planificación o attr).\n");
				break;
		}
	}

	//Esperamos a la finalización de las hebras.
	for(i=0;i<2;i++)
	{
		//error = pthread_join(pthread_self(),NULL); //No se puede hacer un join de sí mismo.
		error = pthread_join(hebras[i], NULL);
		/*
		la funcion join espera a que el hilo invocado termine.
		primer argumento el identificador del hilo
		el segundo es si el hilo devuelve un valor se almacena en la variable que pongamos, si no devuelve nada es NULL

		*/

		//Capturamos los errores que se pueden producir al recoger (join) una hebra.
		switch (error)
		{
			case 0: //Correcto.
				printf("    (Hilo ppal.) Terminó correctamente la hebra ..: %lu\n", (unsigned long int)hebras[i]);
				break;
			case EDEADLK: //Se quiso hacer un join a sí misma.
				printf("    (Hilo ppal.) Se quiso hacer un join a sí mismo.\n");
				break;
			case EINVAL: //La hebra ha sido detached u otra hebra está esperando a que termine.
				printf("    (Hilo ppal.) Se produjo el error EINVAL (la hebra ha sido detached u otra hebra está esperando a que termine.).\n");
				break;
			case ESRCH:  //Se ha hecho un pthread_join sobre una hebra que no existe.
				printf("    (Hilo ppal.) Se produjo el error ESRCH (la hebra no existe).\n");
				break;
		}
	}
	printf("    (Hilo ppal.) Finalización correcta.\n");
	printf("\n");

	//Finalización correcta 
	exit(EXIT_SUCCESS); //devuelve el error que ha sucedido
}


