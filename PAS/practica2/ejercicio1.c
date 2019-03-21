#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <getopt.h>



int main(int argc, char const *argv[]) {
  static struct option long_options[] =
	{
		{"username",	 required_argument, 0, 'u'},
		{"groupname",  required_argument, 0, 'g'},
		{"useruid",  required_argument, 0, 'i'},
		{"groupuid",  required_argument, 0, 'd'},
		{"allgroups",	no_argument, 0, 's'},
    {"allinfo",  required_argument, 0, 'a'},
    {"bactive",  no_argument, 0, 'b'},
    {"help",  no_argument, 0, 'h'},
		{0, 0, 0, 0}
	};
  int option_index=0;
  char *lgn;
  struct passwd *pw;
  struct group *gr;
  char* user="USER";
  FILE* ficherogrupos;
  int c;

  while((c=getopt_long(argc,argv,"u:g:i:d:sa:bh",long_options,&option_index))!=-1){
    switch (c) {
      case 'u':
      pw=getpwnam(optarg);
      if(pw==NULL){
        printf("Error al cargar los datos del usuario %s\n",lgn );
        break;
      }
      else{
        printf("Nombre: %s\n", pw->pw_gecos);
        printf("Login: %s\n", pw->pw_name);
        printf("Password: %s\n", pw->pw_passwd);
        printf("UID: %d\n", pw->pw_uid);
        printf("Home: %s\n", pw->pw_dir);
        printf("Número de grupo principal: %d\n", pw->pw_gid);
      }
      break;
      case 'i':
      pw=getpwuid((uid_t)atoi(optarg));
      if(pw==NULL){
        printf("Error al cargar los datos del usuario %s\n",lgn );
        break;
      }
      else{
        printf("Nombre: %s\n", pw->pw_gecos);
        printf("Login: %s\n", pw->pw_name);
        printf("Password: %s\n", pw->pw_passwd);
        printf("UID: %d\n", pw->pw_uid);
        printf("Home: %s\n", pw->pw_dir);
        printf("Número de grupo principal: %d\n", pw->pw_gid);
      }
      break;
      case 'g':
      gr=getgrnam(optarg);
      if(gr==NULL){
        printf("Error al cargar los datos del grupo\n");
        break;
      }
      else{
        printf("Nombre: %s\n", gr->gr_name);
        printf("Password: %s\n", gr->gr_passwd);
        printf("GID: %d\n", gr->gr_gid);
      }
      break;
      case 'd':
      gr=getgrgid((gid_t)atoi(optarg));
      if(gr==NULL){
        printf("Error al cargar los datos del grupo\n");
        break;
      }
      else{
        printf("Nombre: %s\n", gr->gr_name);
        printf("Password: %s\n", gr->gr_passwd);
        printf("GID: %d\n", gr->gr_gid);
      }
      break;
      case 's':
        ficherogrupos=fopen("/etc/groups","r");
        char nombre[100];
        char pass[100];
        int gid;
        char lista[100];
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
      break;
      case 'a':
      lgn=optarg;
      pw=getpwnam(lgn);
      if(pw==NULL){
        printf("Error al cargar los datos del usuario %s\n",lgn );
        break;
      }
      else{
        printf("Nombre: %s\n", pw->pw_gecos);
        printf("Login: %s\n", pw->pw_name);
        printf("Password: %s\n", pw->pw_passwd);
        printf("UID: %d\n", pw->pw_uid);
        printf("Home: %s\n", pw->pw_dir);
        printf("Número de grupo principal: %d\n", pw->pw_gid);
      }
      gr=getgrgid(pw->pw_gid);
      if(gr==NULL){
        printf("Error al cargar los datos del usuario %s\n",lgn );
        break;
      }
      else{
        printf("Nombre: %s\n", gr->gr_name);
        printf("Password: %s\n", gr->gr_passwd);
        printf("GID: %d\n", gr->gr_gid);
      }
      break;
      case 'b':
      pw=getpwnam(getenv(user));
      gr=getgrgid(pw->pw_gid);
      printf("Nombre: %s\n", gr->gr_name);
      printf("GID: %d\n", gr->gr_gid);
      break;
      case 'h':
      printf("Uso del programa: ./ejercicio1 [opciones]\n" );
      printf("Opciones:\n" );
      printf("-h,--help\t\tImprimir ayuda\n" );
      printf("-u,--username\t\tNombre del usuario\n" );
      printf("-i,--useruid\t\tIdentificador del usuario\n" );
      printf("-g,--groupname\t\tNombre del grupo\n" );
      printf("-d,--groupuid\t\tÏdentificador del grupo\n" );
      printf("-s,--allgroups\t\tMuestra info de todos los grupos del sistema\n" );
      printf("-a,--allinfo\t\tNombre del usuario\n" );
      printf("-b,--bactive\t\tMuestra info del grupo del usuario actual\n" );
      break;
      case '?':
      break;
      default:
      abort();
    }
  }
  if (optind < argc)
	{
		printf("Argumentos ARGV que no son opciones: ");
		while (optind < argc)
				printf("%s ", argv[optind++]);
		putchar ('\n');
	}
  return 0;
}
