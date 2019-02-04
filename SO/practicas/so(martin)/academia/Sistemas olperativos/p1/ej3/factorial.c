#include <stdio.h>

void main(int argc,char *argv[])
{
int i, factor1=atoi(argv[1]);

   for(i=atoi(argv[1]);i>1;i--)
      {
      printf("\nCalculando factorial del argumento %d: %d",atoi(argv[1]),factor1);
      sleep(2);
      factor1=factor1*(i-1);
      }

printf("\n\nEl factorial del argumento %d es %d\n\n",atoi(argv[1]),factor1);

}
