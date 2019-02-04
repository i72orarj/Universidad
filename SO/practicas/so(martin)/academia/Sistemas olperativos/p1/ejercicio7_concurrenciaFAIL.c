/*Cuando un proceso padre crea a un hijo mediante fork(), los descriptores de ficheros que haya en el padre también los “hereda” el hijo. Implemente un programa en el que el padre y el hijo ( o si lo prefiere un padre y dos hijos) hagan varias escrituras en un fichero de texto, intercalando un sleep(1) entre escritura y escritura. Puede hacer que por ejemplo el padre escriba un tipo de caracteres (+++++) y el hijo (hijos) otros distintos (--------). Al termino de la escritura (el padre debe esperar al hijo) cree otro hijo que visualice el fichero para ver si se ha creado correctamente (por consola o usando un comando exec invocando a un editor). Use la linea de argumentos para proporcionar el nombre de fichero a su programa.#include <stdio.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h> 
#include <sys/wait.h>
#define MAX 100

void escribepadre(FILE *f);
void escribehijo(FILE *f,int);

int main (int argc, char **argv)
{
int numerohijos;
char fichero[MAX];
int i,valor,flag;
FILE *f;
pid_t pid;

/* Comprueba que los datos introducidos por la linea de argumentos son correctos */
if (argc !=3){
	printf("Sintaxis incorrecta: %s <fichero.txt> , <número de hijos>\n",argv[0]);
	exit(-1);
}	
	
/* Transfiere los argv[] a sus respectivas variables */
strcpy(fichero,argv[1]);
numerohijos=atoi(argv[2]);	//uso atoi para pasar de char a int

f = fopen(fichero, "w");


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
				escribehijo(f,i);
				sleep(3);
				exit(3);				
	}				
}

/*Esperamos a los hijos*/
while ((flag = wait(&valor)) > 0)
{
	if (WIFEXITED(valor)) {
            printf("child exited, status=%d\n", WEXITSTATUS(valor));
  } else if (WIFSIGNALED(valor)) {  //Para seniales como las de finalizar o matar
      printf("child killed (signal %d)\n", WTERMSIG(valor));
  } else if (WIFSTOPPED(valor)) { //Para cuando se para un proceso. Al usar wait() en vez de waitpid() no nos sirve.
      printf("child stopped (signal %d)\n", WSTOPSIG(valor));
  } else if (WIFCONTINUED(valor)){ //Para cuando se reanuda un proceso parado. Al usar wait() en vez de waitpid() no nos sirve.
		printf("child continued\n");		  
  }
}
if (flag==-1 && errno==ECHILD)
{
	printf("No hay más hijos que esperar, voy a escribir una vez como padre y visualizo el fichero corrupto....:\n");
	escribepadre(f);
	fclose(f);
	if(execlp("cat","cat",fichero,NULL)==-1) //llamada al programa cat 
	{ 
		perror("Fallo en la ejecucion exec de cat\n"); 
		printf("errno value= %d\n", errno); 
		exit(EXIT_FAILURE);
	}	
}
else
{
	printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
	exit(EXIT_FAILURE);
}
return 0;
}



void escribepadre(FILE *f){
char aux[MAX]=" +++++ ";
fputs(aux,f);
fflush(f);
}

void escribehijo(FILE *f, int hijo){
char aux[MAX]=" -----";
char nHijo[MAX];
sprintf(nHijo, "%d", hijo);

strcat(aux,nHijo);

fputs(aux,f);
fflush(f);
}

