#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>

int sumar(int numero){
  int aux=getpid()%10;
  int chilpid,status;
  while(chilpid=wait(&status)>0){
    sleep(2);
    if(WIFEXITED(status)){
      aux=aux+WEXITSTATUS(status);
    }
    else if(WIFSIGNALED(status)){
      printf("Child signaled %d, status %d\n",chilpid,status );
    }
    else if(WIFSTOPPED(status)){
      printf("Child stopped %d, status %d\n",chilpid,status );
    }
    printf("Interaccion %d, PID: %d,PID padre: %d,valor devuelto del hijo: %d\n",numero,getpid(),getppid(),WEXITSTATUS(status) );
    //printf("ITERACION: %d. PID: %d. PID PADRE: %d. Valor recibido:%d\n", numero, getpid(), getppid(), WEXITSTATUS(status));
    exit(aux);
  }
}


int main(int argc, char const *argv[]) {
  pid_t id;
  int i;
  int* devuelve;

  for(i=0;i<5;i++){
    id=fork();
    if(id==-1){
      printf("Error al crear proceso hijo\n" );
    }
    if(id==0);
    else{
      sleep(2);
      sumar(i);

    }

  }

  return 0;
}
