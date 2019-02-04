
//Sistemas Operativos
//Práctica 4. Ejercicio 1
//Programa: productor-consumidor sin espera activa.


#include <stdio.h>
#include <semaphore.h>
#include <errno.h>	//Códigos de error
#include <stdlib.h>


#define T_BUFFER 5	//Tamaño del buffer
#define N_DATOS 100	//Número de datos a producir/consumir


int datos[N_DATOS];	//Datos que serán pasados al buffer para que sean consumidos por el consumidor.
int buffer[T_BUFFER];	//Buffer intermedio de cumunicación.
int e_buffer;		//Elementos del buffer pendientes de producir.


sem_t buffer_producir;	//Para despertar al productor.
sem_t buffer_consumir;	//Para despertar al consumidor.
sem_t buffer_critico;	//Para acceder a la sección critica.




//Para controlar errores en los semáforos.
	void error_en_sem_init(int error);
	void error_en_sem_destroy(int error);
	void error_en_sem_wait(int error);
	void error_en_sem_post(int error);
//



void * productor(void * parametro){

	//Función productor: rellena el buffer para que el consumidor pueda consumir.

	//Declaración de variables.

	int producidos;
	int elemento;
	int suma;
	int error;

	producidos=0;
	suma=0;

	while(producidos!=N_DATOS){

		error=sem_wait(&buffer_producir);	//Se podrán producir un máximo de T_BUFFER elementos sin consumir.
		if(error!=0){
			error_en_sem_wait(error);
		}

			error=sem_wait(&buffer_critico);	//Cerramos la sección crítica.
			if(error!=0){
				error_en_sem_wait(error);
			}

				elemento=*(datos+producidos);		//Producimos un elemento

				buffer[producidos%T_BUFFER]=elemento;	//Añadimos el elemento en el buffer.

				e_buffer=e_buffer-1;			//Reducimos el tamaño disponible del buffer.

				producidos=producidos+1;

				printf("  \nProductor: %d     (Libres=%d)", elemento, e_buffer);

				suma=suma+elemento;

				error=sem_post(&buffer_consumir);	//Despertamos al consumidor.
				if(error!=0){
					error_en_sem_post(error);
				}


			error=sem_post(&buffer_critico);	//Abrimos la sección crítica.
			if(error!=0){
				error_en_sem_post(error);
			}


		//sem_post(&buffer_producir);	//Será el consumidor, cuando haya consumido, el que despierte al productor.

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

	while(consumidos!=N_DATOS){

		error=sem_wait(&buffer_consumir);	//Sólo hay un consumidor.
		if(error!=0){
			error_en_sem_wait(error);
		}

			error=sem_wait(&buffer_critico);	//Cerramos la sección crítica.
			if(error!=0){
				error_en_sem_wait(error);
			}

				elemento=buffer[consumidos%T_BUFFER];	//Extraemos un elemento del buffer.

				buffer[consumidos%T_BUFFER]=-1;		//Eliminamos el contenido del buffer.

				e_buffer=e_buffer+1;			//Aumentamos el tamaño disponible del buffer.
				consumidos=consumidos+1;

				printf("\n          Consumidor: %d      (Por consumir=%d)",elemento,T_BUFFER-e_buffer);

				suma=suma+elemento;

				error=sem_post(&buffer_producir);	//Despertamos al productor.
				if(error!=0){
					error_en_sem_post(error);
				}


			error=sem_post(&buffer_critico);	//Abrimos la sección crítica.
			if(error!=0){
				error_en_sem_post(error);
			}


		//sem_post(&buffer_consumir);	//Será el productor, cuando al menos haya producido 1 elemento, el que despierte al consumidor.

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

	//Inicializamos el array con los datos: 1 .. N_DATOS
	for(i=0;i<N_DATOS;i++){

		*(datos+i)=i+1;

	}

	//Inicializamos el buffer intermedio: 0
	for(i=0;i<T_BUFFER;i++){

		*(buffer+i)=0;

	}

	//Tamaño disponible en el buffer
	e_buffer=T_BUFFER;

	//Incialización de semáforos.
	error=sem_init(&buffer_producir, 0, T_BUFFER);	//Inicialmente se pueden producir T_BUFFER elementos
	if(error!=0){
		error_en_sem_init(error);
	}

	error=sem_init(&buffer_consumir, 0, 0);		//Inicialmente no se puede consumir nada.
	if(error!=0){
		error_en_sem_init(error);
	}

	error=sem_init(&buffer_critico, 0, 1);		//Sólo 1 acceso a la vez a la sección crítica.
	if(error!=0){
		error_en_sem_init(error);
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

	error=sem_destroy(&buffer_producir);
	if(error!=0){
		error_en_sem_destroy(error);
	}

	error=sem_destroy(&buffer_consumir);
	if(error!=0){
		error_en_sem_destroy(error);
	}

	error=sem_destroy(&buffer_critico);
	if(error!=0){
		error_en_sem_destroy(error);
	}


	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);
}



void error_en_sem_wait(int error){

	//Función para controlar los errores que se pueden producir al bloquear un semáforo.

	//Capturamos el error.
	switch (error){

		case EAGAIN: //El semáforo estaba bloqueado.

			printf("    Se produjo el error EAGAIN (El semáforo estaba bloqueado).\n");

			break;

		case EDEADLOCK:  //Interbloqueo.

			printf("    Se produjo el error EDEADLOCK (Interbloqueo).\n");

			break;

		case EINTR:  //Se recibió una señal que interrumpió la solicitud.

			printf("    Se produjo el error EINTR (Se recibió una señal que interrumpió la solicitud).\n");

			break;

		case EINVAL: //Semáforo no válido.

			printf("    Se produjo el error EINVAL (Semáforo no válido).\n");

			break;

		default:  //Otro error no controlado.

			printf("    Se produjo el error %d\n", error);

			break;

	}

	return;

}



void error_en_sem_post(int error){

	//Función para controlar los errores que se pueden producir al desbloquear un semáforo.

	//Capturamos el error.
	switch (error){

		case EINVAL: //Semáforo no válido.

			printf("    Se produjo el error EINVAL (Semáforo no válido).\n");

			break;

		default:  //Otro error no controlado.

			printf("    Se produjo el error %d\n", error);

			break;

	}

	return;

}



void error_en_sem_init(int error){

	//Función para controlar los errores que se pueden producir al inicializar un semáforo.

	//Capturamos el error.
	switch (error){

		case EINVAL:  //El parámetro indicado excede el valor máximo del tamaño del semáforo.

			printf("    (Hilo ppal.) Se produjo el error EINVAL (Se ha excedido el tamaño máximo del semáforo).\n");

			break;

		case ENOSPC:  //Falta de recursos o se ha alcanzado el máximo de semáforos.

			printf("    (Hilo ppal.) Se produjo el error ENOSPC (Falta de recursos o se ha alcanzado el máximo de semáforos).\n");

			break;

		case EPERM:  //El proceso no tiene los recursos necesarios para inicializar el semáforo.

			printf("    (Hilo ppal.) Se produjo el error EPERM (Falta de recursos para inicializar el semáforo).\n");

			break;

		default:  //Otro error no controlado.

			printf("    Se produjo el error %d\n", error);

			break;

	}

}



void error_en_sem_destroy(int error){

	//Función para controlar los errores que se pueden producir al destruir un semáforo.

	//Capturamos el error.
	switch (error){

		case EBUSY: //El semáforo está cerrado y hay procesos bloqueados en él.

			printf("    (Hilo ppal.) Se produjo el error EBUSY (El semáforo está cerrado y hay procesos bloqueados en él).\n");

			break;

		case EINVAL:  //Semáforo no válido.

			printf("    (Hilo ppal.) Se produjo el error EINVAL (Semáforo no válido).\n");

			break;

		default:  //Otro error no controlado.

			printf("    Se produjo el error %d\n", error);

			break;

	}

}


