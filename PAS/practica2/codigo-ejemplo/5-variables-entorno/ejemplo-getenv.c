#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//Ejecución:  %$>./a.out

int main(void)
{
    char *lang = "LANG";
    char *home = "HOME";
    char* user="USER";
    char *value;

	 //Si el valor devuelto en value es "ES" imprime Español, sino imprime INGLES.
    value = getenv(lang);
    //printf("%s\n",value );
    if (strstr(value,"ES"))
    {
        printf("\nLa carpeta del usuario/a %s es: %s\n", getenv(user),getenv(home));
    }
    else
    {
        printf("\nUser's home folder is: %s\n", getenv(home));
    }
    exit(0);
}
