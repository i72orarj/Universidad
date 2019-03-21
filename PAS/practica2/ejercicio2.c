#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>


int esPrimo(int a){
  int i,cont=0;
  for(i=1;i<a;i++){
    if(a%i==0){
      cont++;
    }
  }
  return cont;
}

int main(int argc, char const *argv[]) {
  pid_t flag;
  int status;
  int fildes[2];
  int fildes2[2];
  const int BSIZE = 100;
  char buf[BSIZE],buf2[BSIZE];
  ssize_t nbytes,nbytes2;
  int num1,num2,num3,num4;
  char aux[BSIZE];

  status=pipe(fildes);
  if(status==-1){
    perror("Error en pipe");
    exit(EXIT_FAILURE);
  }
  status=pipe(fildes2);
  if(status==-1){
    perror("Error en pipe2");
    exit(EXIT_FAILURE);
  }
  switch (fork()) {
    case -1:
    perror("Fallo al crear el hijo");
    exit(EXIT_FAILURE);
    break;
    case 0://hijo
    close(fildes[1]);
    nbytes=read(fildes[0],buf,BSIZE);
    if(nbytes==-1){
      printf("HIJO Error al leer\n" );
      exit(EXIT_FAILURE);
    }
    else if(nbytes==0){
      printf("HIJO La tuberia 1 esta cerrada\n" );
    }
    else{
      printf("HIJO Leido %s correctamente\n",buf );
      sscanf(buf,"%d;%d",&num3,&num4);;
    }
    if(close(fildes[0])==-1){
      perror("HIJO Error al cerrar la lectura en tuberia 1");
      exit(EXIT_FAILURE);
    }
    else{
      printf("HIJO Tuberia 1 cerrada\n" );
    }
    //close(fildes2[0]);
    if (close(fildes2[0]) == -1){
      perror("HIJO Error en close2");
      exit(EXIT_FAILURE);
    }
    else{
      printf("HIJO Lectura en tuberia 2 cerrada\n" );
    }
    if(esPrimo(num3)==1&&esPrimo(num4)==1){
      if(num3-num4==2||num4-num3==2){
        write(fildes2[1],"gemelos",10);
        printf("HIJO He escrito en la tuberia 2\n" );
      }
      else{
        write(fildes2[1],"primos",8);
        printf("HIJO He escrito en la tuberia 2\n" );
      }
    }
    else{;
      write(fildes2[1],"no-primos",11);
      printf("HIJO He escrito en la tuberia 2\n" );
    }
    close(fildes2[1]);
    printf("HIJO Tuberia 2 cerrada\n" );
    exit(EXIT_SUCCESS);
    break;
    default://padre
    if (close(fildes[0]) == -1){
			perror("Error en close");
			exit(EXIT_FAILURE);
		}
    printf("PADRE Introduzca dos numeros\n" );
    scanf("%d",&num1 );
    scanf("%d",&num2 );
    sprintf(aux,"%d;%d",num1,num2);
    write(fildes[1],aux,BSIZE);
    printf("PADRE Escrito %s en la tuberia 1\n",aux );
		if (close(fildes[1]) == -1){
			perror("Error en close");
			exit(EXIT_FAILURE);
		}
		else{
			printf("PADRE Tuberia 1 cerrada.\n");
    }
    if (close(fildes2[1]) == -1){
      perror("Error en close");
      exit(EXIT_FAILURE);
    }
    nbytes2=read(fildes2[0],buf2,BSIZE);
    if(nbytes2==-1){
      printf("PADRE Error al leer en tuberia 2\n" );
      exit(EXIT_FAILURE);
    }
    else if(nbytes2==0){
      printf("PADRE La tuberia 2 esta cerrada\n" );
    }
    else{
      printf("PADRE Leido %s correctamente\n",buf2 );
    }
    close(fildes2[0]);
    printf("PADRE Tuberia 2 cerrada\n" );
		while ( (flag=wait(&status)) > 0 ){
			if (WIFEXITED(status)){
				printf("Proceso Padre, Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
			}
      else if (WIFSIGNALED(status)){
				printf("Proceso Padre, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
			}
      else if (WIFSTOPPED(status)){
				printf("Proceso Padre, Hijo con PID %ld parado al recibir la señal %d\n", (long int)flag,WSTOPSIG(status));
			}
      else if (WIFCONTINUED(status)){
				printf("Proceso Padre, Hijo con PID %ld reanudado\n",(long int) flag);
			}
		}
		if (flag==(pid_t)-1 && errno==ECHILD){
			printf("Proceso Padre, valor de errno = %d, definido como %s, no hay más hijos que esperar!\n", errno, strerror(errno));
		}
		else{
			printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
    break;
  }

  return 0;
}
