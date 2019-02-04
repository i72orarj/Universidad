#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <unistd.h>

int suma;

int main(int argc, char const *argv[]) {
  if(argc!=2){
    printf("Cantidad incorrecta de argumentos\n");
    printf("Acompañe el ejecutable con el numero de procesos\n");
    return 0;
  }
  pid_t id;
  int nProcesos,i;
  suma=0;
  nProcesos=atoi(argv[1]);
  for(i=0;i<nProcesos;i++){
    id=fork();
    if(id==-1){
      printf("error\n");
    }
    else if(id==0){
      printf("Esto es el hijo %d\n",i );
      printf("id=%d,id padre=%d\n",getppid(),getpid() );
    }
    else{
      sleep(3);
      printf("Esto es el padre %d\n",i );

    }
  }


  return 0;
}
