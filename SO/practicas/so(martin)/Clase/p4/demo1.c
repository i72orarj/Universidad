//
//	Programa 1 para demostraci�n de Memoria compartida.
//
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//	Conseguimos una clave para la Memoria compartida. Todos los
//	procesos que quieran compartir la Memoria, deben obtener la misma
//	clave.

#define Clave (key_t) 234

//  La clave tambi�n se puede conseguir por medio de la funci�n ftok.
//	A esta funci�n se le pasa un fichero cualquiera que exista y est�
//	accesible (todos los procesos deben pasar el mismo fichero) y un
//	entero cualquiera (todos los procesos el mismo entero). El siguiente
//  c�digo deber�a colocarse al principio del main (ver c�digo comentado)

#define MAX 10

int main()
{
	//key_t Clave;
	int Id_Memoria;
	int *Memoria = NULL;
	int i,j;
    
    /* Clave = ftok ("/bin/ls", 33);
     if (Clave == -1)
     {
     printf("No consigo clave para Memoria compartida\n");
     exit(0);
     }
     */
    
	//  Una vez tenemos la Clave:
	//	Creamos la Memoria con la clave reci�n conseguida. Para ello llamamos
	//	a la funci�n shmget pas�ndole la clave, el tama�o de Memoria que
	//	queremos reservar (100 enteros en nuestro caso) y unos flags.
	//	Los flags son  los permisos de lectura/escritura/ejecucion 
	//	para propietario, grupo y otros (es el 777 en octal) y el 
	//	flag IPC_CREAT para indicar que cree la Memoria.
	//	La funci�n nos devuelve un identificador para la Memoria reci�n
	//	creada.
	//	 
	Id_Memoria = shmget (Clave, sizeof(int)*100, 0777 | IPC_CREAT);
	if (Id_Memoria == -1)
	{
		printf("No consigo Id para Memoria compartida\n");
		exit(0);
	}

	//
	//	Una vez creada la Memoria, hacemos que uno de nuestros punteros
	//	apunte a la zona de Memoria reci�n creada. Para ello llamamos a
	//	shmat, pas�ndole el identificador obtenido anteriormente y un
	//	par de par�metros extra�os, que con ceros vale.
	//
	Memoria = (int *)shmat (Id_Memoria, (char *)0, 0);
	if (Memoria == NULL)
	{
		printf("No consigo Memoria compartida");
		exit(0);
	}

	//
	//	Ya podemos utilizar la Memoria.
	//	Escribimos cosas en la Memoria. Los n�meros de 1 a 10 esperando
	//	un segundo entre ellos. Estos datos ser�n los que lea el otro
	//	proceso.
	//
    
	for (i=0; i<10; i++)
	{
		Memoria[i] = i;
		printf("Escrito %d\n",i);

		sleep (1);
	}

	//
	//	Terminada de usar la Memoria compartida, la liberamos.
	//
	shmdt ((char *)Memoria);
	shmctl (Id_Memoria, IPC_RMID, (struct shmid_ds *)NULL);
}
