#include <stdio.h>
#include <semaphore.h>
#include <errno.h>	//Códigos de error
#include <stdlib.h>

#define T_BUFFER 5	//Tamaño del buffer
#define N_DATOS 20	//Número de datos a producir/consumir

//int buffer[T_BUFFER];	//Buffer intermedio de cumunicación.
//int e_buffer;		//Elementos del buffer pendientes de producir.
int cont;

sem_t buffer_producir;	//Para despertar al productor.
sem_t buffer_consumir;	//Para despertar al consumidor.
sem_t buffer_critico;	//Para acceder a la sección critica.

void * productor(void * parametro){

	int producidos, elemento, suma, *v;

	v = (int *)parametro;

	v = (int *)malloc(sizeof(int));

	producidos=0;
	
	while(1){

		sem_wait(&buffer_producir);	//Se podrán producir un máximo de T_BUFFER elementos sin consumir.

		sem_wait(&buffer_critico);	//Cerramos la sección crítica.

		//elemento=*(datos+producidos);	//Producimos un elemento

		//buffer[producidos%T_BUFFER]=elemento;	//Añadimos el elemento en el buffer.

		//e_buffer=e_buffer-1;			//Reducimos el tamaño disponible del buffer.

		//producidos=producidos+1;

		printf("Produciendo el productor: %d     (Quedan=%d)\n", *v+1, cont);
		sleep(2);
		*v=*v+1;
		cont++;

		sem_post(&buffer_critico);	//Abrimos la sección crítica.
		
		sem_post(&buffer_consumir);	//Despertamos al consumidor.
				
		//sem_post(&buffer_producir);	//Será el consumidor, cuando haya consumido, el que despierte al productor.

	}


pthread_exit(NULL);
}

void * consumidor(void * parametro){

	int consumidos, elemento, suma, *v;

	consumidos=0;
	v = (int *)parametro;

	v = (int *)malloc(sizeof(int));

	while(1){

		sem_wait(&buffer_consumir);	//Sólo hay un consumidor.
		
		sem_wait(&buffer_critico);	//Cerramos la sección crítica.
		
		//elemento=buffer[consumidos%T_BUFFER];	//Extraemos un elemento del buffer.

		//buffer[consumidos%T_BUFFER]=-1;		//Eliminamos el contenido del buffer.

		//e_buffer=e_buffer+1;			//Aumentamos el tamaño disponible del buffer.

		//consumidos=consumidos+1;

		printf("Consumiendo el consumidor: %d      (Por consumir=%d)\n",*v+1 ,cont);
		sleep(2);
		*v=*v+1;
		cont--;

		sem_post(&buffer_producir);	//Despertamos al productor.
				
		sem_post(&buffer_critico);	//Abrimos la sección crítica.
			
		//sem_post(&buffer_consumir);	//Será el productor, cuando al menos haya producido 1 elemento, el que despierte al consumidor.
	}

pthread_exit(NULL);
}


int main(){

	int i;
	int datos[N_DATOS];	//Datos que serán pasados al buffer para que sean consumidos por el consumidor.
	pthread_t hebras[2];

	//Inicializamos el array con los datos: 1 .. N_DATOS
	for(i=0;i<N_DATOS;i++){

		*(datos+i)=i+1;
	}

	sem_init(&buffer_producir, 0, T_BUFFER); //Inicialmente se pueden producir T_BUFFER elementos en este caso 5
	sem_init(&buffer_consumir, 0, 0); //Inicialmente no se puede consumir nada.
	sem_init(&buffer_critico, 0, 1); //Sólo 1 acceso a la vez a la sección crítica.

	//Creamos las 2 hebras: Productor / Consumidor.
	for(i=0;i<2;i++){

		if(i==0){

			//Productor
			cont=5;
			pthread_create( &(hebras[i]), NULL, (void *) productor, (void *)&datos[i]);
		}else{
			//Consumidor
			cont=5;
			pthread_create( &(hebras[i]), NULL, (void *) consumidor, (void *)&datos[i]);
		}
	}

	//Esperamos a la finalización de las hebras.
	for(i=0;i<2;i++){

		pthread_join(hebras[i], NULL); 
	}

return 0;
}
