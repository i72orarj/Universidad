/*Cuando un proceso padre crea a un hijo mediante fork(), los descriptores de ficheros que haya en el padre también los “hereda” el hijo. Implemente un programa en el que el padre y el hijo ( o si lo prefiere un padre y dos hijos) hagan varias escrituras en un fichero de texto, intercalando un sleep(1) entre escritura y escritura. Puede hacer que por ejemplo el padre escriba un tipo de caracteres (+++++) y el hijo (hijos) otros distintos (--------). Al termino de la escritura (el padre debe esperar al hijo) cree otro hijo que visualice el fichero para ver si se ha creado correctamente (por consola o usando un comando exec invocando a un editor). Use la linea de argumentos para proporcionar el nombre de fichero a su programa.#include <stdio.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h> 
#include <sys/wait.h>
#define MAX 100

void escribepadre(char fichero[MAX]);
void escribehijo(char fichero[MAX],int);

int main (int argc, char **argv)
{
int estadoHijo;
int numerohijos;
char fichero[MAX];
int i;

/* Comprueba que los datos introducidos por la linea de argumentos son correctos */
if (argc !=3){
	printf("Sintaxis incorrecta: %s <fichero.txt> , <número de hijos>\n",argv[0]);
	exit(-1);
}	
	
/* Transfiere los argv[] a sus respectivas variables */
strcpy(fichero,argv[1]);
numerohijos=atoi(argv[2]);	//uso atoi para pasar de char a int

pid_t pid;
for (i=0;i<numerohijos;i++)
{
	pid=fork();
	switch (pid)
	{
		case -1: /* Error del fork() */
				perror("Fork() error\n");
				printf("errno value= %d\n", errno);
				exit(EXIT_FAILURE);		
		case 0: /* proceso hijo */
				sleep(3);
         	//printf("Soy el proceso hijo número %d: %d y mi padre es %d\n",i+1, getpid(), getppid());				
				printf("Hijo escribiendo...\n");
				escribehijo(fichero,i);
				sleep(3);
				exit(3);				
 		default:/* proceso padre */	      	
			wait(&estadoHijo); //el padre se espera hasta q no haya ningun hijo ejecutandose
			printf("Padre escribiendo...\n");
			escribepadre(fichero);

			//Si se termina bien, "estadoHijo" cogerá  el valor devuelto por éste 3...
			if (WIFEXITED(estadoHijo) != 0){ 
				printf ("\nPadre: Mi hijo ha salido. Devuelve %d\n\n", WEXITSTATUS(estadoHijo));
			}
			
			//Comprobamos si quedan mas hijos.		
			if(errno==ECHILD) {
					printf("No hay hijos que esperar\n");	
					printf("Padre durmiendo de nuevo....\n");
					sleep(10);
			}
	}				
}
printf("\n** Visualización del archivo %s ** \n", fichero);
if(execlp("cat","cat",fichero,NULL)==-1) //llamada al programa cat 
{ 
	perror("Fallo en la ejecucion exec de cat\n"); 
	printf("errno value= %d\n", errno); 
	exit(EXIT_FAILURE);
}	

return 0;
}



void escribepadre(char fichero[MAX]){

FILE *fo;
char aux[MAX]=" +++++ ";


fo=fopen(fichero, "a");

	if(fo==NULL){
		printf("Error\n");
		exit(-1);
	}
	
fputs(aux,fo);
fflush(fo);
fclose(fo);

}

void escribehijo(char fichero[MAX], int hijo){

FILE *fo;
char aux[MAX]=" -----";
char nHijo[MAX];
sprintf(nHijo, "%d", hijo);

strcat(aux,nHijo);

fo=fopen(fichero, "a");

	if(fo==NULL){
		printf("Error\n");
		exit(-1);
	}
	
fputs(aux,fo);

fflush(fo);
fclose(fo);

}

