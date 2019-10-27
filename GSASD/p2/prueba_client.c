/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "prueba.h"


void
calculadora_prog_1(char *host,int a, int b)
{
	CLIENT *clnt;
	int  *result_1;
	operandos  suma_1_arg;
	suma_1_arg.a=a;
	suma_1_arg.b=b;
	int  *result_2;
	operandos  multiplicacion_1_arg;
	multiplicacion_1_arg.a=a;
	multiplicacion_1_arg.b=b;
	double  *result_3;
	operandos  division_1_arg;
	division_1_arg.a=a;
	division_1_arg.b=b;
	int  *result_4;
	operandos  resta_1_arg;
	resta_1_arg.a=a;
	resta_1_arg.b=b;

#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORA_PROG, CALCULADORA_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = suma_1(&suma_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_2 = multiplicacion_1(&multiplicacion_1_arg, clnt);
	if (result_2 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_3 = division_1(&division_1_arg, clnt);
	if (result_3 == (double *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_4 = resta_1(&resta_1_arg, clnt);
	if (result_4 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	printf("El resultado de la suma es: %d\n",*result_1 );
	printf("El resultado de la resta es: %d\n",*result_4 );
	printf("El resultado de la multiplicacion es: %d\n",*result_2 );
	printf("El resultado de la division es: %.2f\n",*result_3 );
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;
	int a,b;
	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	printf("Introduzca dos valores: \n" );
	scanf("%d",&a );
	scanf("%d",&b );
	calculadora_prog_1 (host,a,b);
exit (0);
}
