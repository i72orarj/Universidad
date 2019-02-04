#include <stdio.h>


int main(int argc, char **argv)
{
	int suma =0;
	int i;
	int n=atoi(argv[1]);

		for(i=0;i<=n;i++)
		{
			suma+=i;
		}
		printf("El sumatorio de {%d} es [%d]\n", n, suma);
}