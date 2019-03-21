#include <stdio.h>


int main(int argc, char const *argv[]) {
  char nombre[100],pass[100],lista[100];
  int gid;
  FILE*  ficherogrupos=fopen("/etc/groups","r");
  if(ficherogrupos==NULL){
    printf("Fallo al abrir el fichero\n" );
    return 0;
  }
  while(fscanf(ficherogrupos,"%s:%s:%d:%s\n",nombre,pass,&gid,lista)!=EOF){
    printf("Nombre: %s\n",nombre );
    printf("Password: %s\n",pass);
    printf("GID: %d\n",gid );
    printf("Lista de usuarios en el grupo: %s\n",lista );
  }
  return 0;
}
