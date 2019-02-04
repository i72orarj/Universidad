//Sistemas Operativos
//Práctica 3. Ejercicio 2
//Programa que crea tres hebras y cada hebra escribe un carácter diferente, siendo éste escrito 5 veces seguidas en pantalla. el main o hebra principal
//también debe escribir un carácter.
// --> hebra1 '*'
// --> hebra1 '?'
// --> hebra1 '+'
// --> hebra ppal. '-'


#include <stdio.h>
#include <pthread.h>
#include <errno.h>	//Códigos de error
#include <string.h>	//Cadenas
#include <stdlib.h>

//Para controlar errores en los semáforos.
void error_en_destroy_mutex(int error);
void error_en_init_mutex(int error);
void error_en_unlock_mutex(int error);
void error_en_lock_mutex(int error);

pthread_mutex_t mutex1;	//declaracion Semáforo binario


void * imprime_caracter(void * parametro)
{
	//Función que imprime, cinco veces seguidas, el carácter que recibe por parámetro.
	//Declaración de variables.
	char *caracter;
	int i;
	int error;

	//Conversión de void * a char *
	caracter = (char *)parametro;
	error=pthread_mutex_lock(&mutex1);	//Bloqueamos el semáforo para acceder a la sección crítica.
	if(error!=0)
		//Se produjo un error.
		error_en_lock_mutex(error);


	for(i=0;i<5;i++)
	{
		sleep(1);
		printf("%c", *caracter);
		fflush(stdout);
	}

	printf(" ");

	error=pthread_mutex_unlock(&mutex1);	//Desbloqueamos el semáforo una vez procesada la sección crítica.
	if(error!=0)
		//Se produjo un error.
		error_en_unlock_mutex(error);

	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);
}


int main()
{
	//Declaración de variables.
	pthread_t hebras[3];
	char caracteres[5]="*?+-";

	int i;
	int error;
	int error1;

	printf("\n\n");

	//Inicializamos el semáforo.
	error=pthread_mutex_init (&mutex1,NULL);   //la funcion mutex_init es para inicializar, el primer campo es el semaforo, el segundo el valor por el que inicializa
	if(error!=0)
		//Se produjo un error.
		error_en_init_mutex(error);

	//Creamos las 3 hebras.
	for(i=0;i<3;i++)
	{
		error = pthread_create( &(hebras[i]), NULL, (void *) imprime_caracter, (void *) &caracteres[i]);
		//Bloqueamos el semáforo para acceder a la sección crítica. Esto vale para que entre un mesaje de error de los del switch de más abajo
		//no se intercale una posible escritura por pantalla de otra hebra.
		error1=pthread_mutex_lock(&mutex1);	
		if(error1!=0)
			//Se produjo un error.
			error_en_lock_mutex(error1);

		//Capturamos los errores que se pueden producir al crear una hebra.
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

		error=pthread_mutex_unlock(&mutex1);	//Desbloqueamos el semáforo una vez procesada la sección crítica.
		if(error!=0)
			//Se produjo un error.
			error_en_unlock_mutex(error);
	}


	//Ahora imprime el main.

	error=pthread_mutex_lock(&mutex1);	//Bloqueamos el semáforo para acceder a la sección crítica.
	if(error!=0)
		//Se produjo un error.
		error_en_lock_mutex(error);

	for(i=0;i<5;i++)
	{
		sleep(1);
		printf("%c", caracteres[3]);
		fflush(stdout);
	}

	error=pthread_mutex_unlock(&mutex1);	//Desbloqueamos el semáforo una vez procesada la sección crítica.
	if(error!=0)//Se produjo un error.
		error_en_unlock_mutex(error);

	printf("\n");
	//Esperamos a la finalización de las hebras.
	for(i=0;i<3;i++)
	{
		error = pthread_join(hebras[i], NULL);
		error1=pthread_mutex_lock(&mutex1);	//Bloqueamos el semáforo para acceder a la sección crítica.
		if(error1!=0)			//Se produjo un error.
			error_en_lock_mutex(error1);

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

		error=pthread_mutex_unlock(&mutex1);	//Desbloqueamos el semáforo una vez procesada la sección crítica.
		if(error!=0)
			//Se produjo un error.
			error_en_unlock_mutex(error);
	}

	printf("    (Hilo ppal.) Finalización correcta.\n");
	printf("\n\n");
	//Liberamos el semáforo.
	error=pthread_mutex_destroy(&mutex1);
	if(error!=0)		//Se produjo un error.
		error_en_destroy_mutex(error);

	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);
}



void error_en_lock_mutex(int error)
{
	//Función para controlar los errores que se pueden producir al bloquear un semáforo.

	//Capturamos el error.
	switch (error)
	{

		case EAGAIN: //Se ha excedido el máximo número de cierres recursivos.

			printf("    Se produjo el error EAGAIN (Se ha excedido el máximo número de cierres recursivos).\n");

			break;

		case EINVAL: //La hebra actual tiene mayor prioridad que el semáforo.

			printf("    Se produjo el error EINVAL (La hebra actual tiene mayor prioridad que el semáforo).\n");

			break;

		case ENOTRECOVERABLE: //No se puede recuperar el estado del semáforo.

			printf("    Se produjo el error ENOTRECOVERABLE (No se puede recuperar el estado del semáforo).\n");

			break;

		case EBUSY:  //Semáforo cerrado.

			printf("    Se produjo el error EBUSY (Semáforo cerrado).\n");

			break;

		case EDEADLOCK:  //Interbloqueo.

			printf("    Se produjo el error EDEADLOCK (Interbloqueo).\n");

			break;

		default:  //Otro error no controlado.

			printf("    Se produjo el error %d\n", error);

			break;

	}

	return;

}



void error_en_unlock_mutex(int error)
{
	//Función para controlar los errores que se pueden producir al desbloquear un semáforo.

	//Capturamos el error.
	switch (error)
	{

		case EPERM: //El tipo de semáforo requiere que la hebra sea su propietario, y no lo es.

			printf("    Se produjo el error EPERM (El tipo de semáforo requiere que la hebra sea su propietario, y no lo es).\n");

			break;

		default:  //Otro error no controlado.

			printf("    Se produjo el error %d\n", error);

			break;
	}
	return;
}



void error_en_init_mutex(int error)
{
	//Función para controlar los errores que se pueden producir al inicializar un semáforo.

	//Capturamos el error.
	switch (error)
	{

		case EAGAIN: //El sistema no tiene recursos para inicializar el semáforo.

			printf("    (Hilo ppal.) Se produjo el error EAGAIN (Sin recursos para inicializar el semáforo).\n");

			break;

		case ENOMEM: //Memoria insuficiente para inicializar el semáforo

			printf("    (Hilo ppal.) Se produjo el error ENOMEM (Memoria insuficiente para inicialiar el semáforo).\n");

			break;

		case EPERM:  //El proceso no tiene privilegios para inicializar el semáforo.

			printf("    (Hilo ppal.) Se produjo el error EPERM (Sin privilegios para inicializar el semáforo).\n");

			break;

		case EINVAL:  //Los atributos enviados indican que se trata de un ' robust mutex ' pero no se ha configurado el atributo process-shared

			printf("    (Hilo ppal.) Se produjo el error EINVAL (Error en los atributos al indicar que se trata de un ' robust mutex ').\n");

			break;
	}

}

void error_en_destroy_mutex(int error)
{
	//Función para controlar los errores que se pueden producir al destruir un semáforo.

	//Capturamos el error.
	switch (error)
	{

		case EBUSY: //El semáforo está cerrado.

			printf("    (Hilo ppal.) Se produjo el error EBUSY (El semáforo está cerrado).\n");

			break;

		case EINVAL:  //Semáforo no válido.

			printf("    (Hilo ppal.) Se produjo el error EINVAL (Semáforo no válido).\n");

			break;
	}

}
