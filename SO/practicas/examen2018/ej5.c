#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>

void sumar(int numero){
  int aux=getpid()%10;
  int chilpid,status;
  while(chilpid=wait(&status)>0){
    sleep(2);
    if(WIFEXITED(status)){
      aux=aux+WEXITSTATUS(status);
    }
    else if(WIFSIGNALED(status)){
      printf("PID=%d signaled,status=%d\n",chilpid,status );
    }
    else if(WIFSTOPPED(status)){
      printf("PID=%d stopped,status=%d\n",chilpid,status );
    }
    printf("ITERACION: %d. PID: %d. PID PADRE: %d. Valor recibido:%d\n",
        numero, getpid(), getppid(), WEXITSTATUS(status));
    exit(aux);
  }
}



int main(int argc, char const *argv[]) {
  pid_t id;

  if(argc!=2){
    printf("Cantidad incorrecta de argumentos\n" );
    return 0;
  }
  int nProcesos=atoi(argv[1]);
  int chilpid,status;
  int i;
  for(i=0;i<nProcesos;i++){
    id=fork();
    if(id==-1);
    if(id==0);
    else{
      sumar(i);
    }
  }
  return 0;
}
