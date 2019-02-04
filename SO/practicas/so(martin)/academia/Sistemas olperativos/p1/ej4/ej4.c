#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void main(){

  pid_t pid;

  printf("\n");

  pid = fork();

  if (pid == -1){

    perror("fork error");
    printf("errno value= %d\n", errno);
    exit(-1);

    }else if(pid==0){

    printf ("\nSoy el hijo, mi PID es %d y el de mi padre es %d\n",getpid(),getppid());   
  	exit(-1);

    }else{

    sleep(15);
    printf("Soy el padre, mi PID es %d.\n",getpid());
    sleep(3);
    exit(-1);
    
    }
  
printf("\nFin del programa...\n\n");

}
