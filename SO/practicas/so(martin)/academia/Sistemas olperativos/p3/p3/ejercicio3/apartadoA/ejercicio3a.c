
//Sistemas Operativos
//Práctica 3. Ejercicio 3
//Programa: productor-consumidor con espera activa.


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
//


pthread_mutex_t s;	//Semáforo binario.

int e_buffer;		//Tamaño del buffer.

int datos[20];		//Datos que serán pasados al buffer para que sean consumidos por el consumidor.
int buffer[5];		//Buffer intermedio de cumunicación.


void * productor(void * parametro){

	//Función productor: rellena el buffer para que el consumidor pueda consumir.

	//Declaración de variables.

	int producidos;
	int elemento;
	int suma;
	int error;

	producidos=0;
	suma=0;

	while(producidos!=20){

		//Producimos un elemento
		elemento=*(datos+producidos);	//elemento=datos[producidos];

		while(e_buffer==0){	//Esperamos mientras el buffer esté lleno (no hay espacio para añadir).

			printf("\n    ** Productor espera activa");

		};

		error=pthread_mutex_lock(&s);
			if(error!=0){

				//Se produjo un error.
				error_en_lock_mutex(error);

			}


			//Añadimos el elemento en el buffer.
			buffer[producidos%5]=elemento;

			e_buffer=e_buffer-1;

			producidos=producidos+1;

			printf("\n  Productor: %d     (Libres=%d)", elemento, e_buffer);

			suma=suma+elemento;

		error=pthread_mutex_unlock(&s);
		if(error!=0){

			//Se produjo un error.
			error_en_unlock_mutex(error);

		}
		//usleep(random()%2000+1000); //aleatorio entre 1000 y 2000 milisegundos
	}

	printf("\n   --> Productor total producidos ..: %d", suma);

	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);

}

void * consumidor(void * parametro){

	//Función consumidor: recupera del buffer los elementos que ha producido el productor.

	//Declaración de variables.

	int consumidos;
	int elemento;
	int suma;
	int error;

	consumidos=0;
	suma=0;

	while(consumidos!=20){

		while(e_buffer==5){	//Esperamos mientras el buffer esté vacío.

			printf("\n    ** Consumidor espera activa");

		};

		error=pthread_mutex_lock(&s);
			if(error!=0){

				//Se produjo un error.
				error_en_lock_mutex(error);

			}

			//Extraemos un elemento del buffer.
			elemento=buffer[consumidos%5];

			buffer[consumidos%5]=-1;	//Eliminamos el contenido del buffer.

			e_buffer=e_buffer+1;

			consumidos=consumidos+1;

			printf("\n          Consumidor: %d      (Por consumir=%d)",elemento,5-e_buffer);

			suma=suma+elemento;

		error=pthread_mutex_unlock(&s);
		if(error!=0){

			//Se produjo un error.
			error_en_unlock_mutex(error);

		}
		//usleep(random()%3000+1000); //aleatorio entre 1000 y 3000 milisegundos
	}

	printf("\n   --> Consumidor total consumidos .: %d", suma);

	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);

}


int main(){

	//Declaración de variables.

	pthread_t hebras[2];

	int i;
	int error;


	printf("\n\n");

	//Inicializamos el array con los datos: 1 .. 100
	for(i=0;i<100;i++){

		*(datos+i)=i+1;

	}

	//Inicializamos el buffer intermedio: 0
	for(i=0;i<5;i++){

		*(buffer+i)=0;

	}

	//Tamaño disponible en el buffer
	e_buffer=5;

	//Inicializamos el semáforo.
	error=pthread_mutex_init(&s,NULL);
	if(error!=0){

		//Se produjo un error.
		error_en_init_mutex(error);

	}



	//Creamos las 2 hebras: Productor / Consumidor.
	for(i=0;i<2;i++){

		if(i==0){

			//Productor
			error = pthread_create( &(hebras[i]), NULL, (void *) productor, NULL);

		}else{

			//Consumidor
			error = pthread_create( &(hebras[i]), NULL, (void *) consumidor, NULL);

		}
		
		//Capturamos los errores que se pueden producir al crear una hebra.
		switch (error){

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
	for(i=0;i<2;i++){

		error = pthread_join(hebras[i], NULL);

		//Capturamos los errores que se pueden producir al recoger (join) una hebra.
		switch (error){

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

	//Imprimimos el estado del buffer
	printf("\n          Unidades libres en el buffer ..: %d\n",e_buffer);

	printf("    (Hilo ppal.) Finalización correcta.\n");

	printf("\n\n");

	//Liberamos el semáforo.
	error=pthread_mutex_destroy(&s);
	if(error!=0){

		//Se produjo un error.
		error_en_destroy_mutex(error);

	}


	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);
}


void error_en_lock_mutex(int error){

	//Función para controlar los errores que se pueden producir al bloquear un semáforo.

	//Capturamos el error.
	switch (error){

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


void error_en_unlock_mutex(int error){

	//Función para controlar los errores que se pueden producir al desbloquear un semáforo.

	//Capturamos el error.
	switch (error){

		case EPERM: //El tipo de semáforo requiere que la hebra sea su propietario, y no lo es.

			printf("    Se produjo el error EPERM (El tipo de semáforo requiere que la hebra sea su propietario, y no lo es).\n");

			break;

		default:  //Otro error no controlado.

			printf("    Se produjo el error %d\n", error);

			break;

	}

	return;

}


void error_en_init_mutex(int error){

	//Función para controlar los errores que se pueden producir al inicializar un semáforo.

	//Capturamos el error.
	switch (error){

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


void error_en_destroy_mutex(int error){

	//Función para controlar los errores que se pueden producir al destruir un semáforo.

	//Capturamos el error.
	switch (error){

		case EBUSY: //El semáforo está cerrado.

			printf("    (Hilo ppal.) Se produjo el error EBUSY (El semáforo está cerrado).\n");

			break;

		case EINVAL:  //Semáforo no válido.

			printf("    (Hilo ppal.) Se produjo el error EINVAL (Semáforo no válido).\n");

			break;

	}

}


