#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>

/* --------------------------------------------------------------------------------------

 Env�a un n�mero aleatorio al servidor, quien el devuelve el n�mero incremetnado

---------------------------------------------------------------------------------------- */
int main(int argc, char const *argv[])
{

		/*----------------------------------------------------
			Descriptor del socket y buffer para orden
		-----------------------------------------------------*/
		int Socket_Cliente;
		char orden[256];

   	/* -----------------------------------------------------
   		Informaci\ufffdn del Servidor
   	-----------------------------------------------------*/
   	struct sockaddr_in Servidor;
   	socklen_t Longitud_Servidor;


   	/* --------------------------------------------------
			Se abre el socket cliente
		---------------------------------------------------*/
		Socket_Cliente = socket (AF_INET, SOCK_DGRAM, 0);
		if (Socket_Cliente == -1)
		{
			printf ("No se puede abrir el socket cliente\n");
    		exit (-1);
		}

 		/*---------------------------------------------------------------------
			Necesitamos una estructura con la informaci\ufffdn del Servidor
			para poder solicitarle un servicio.
   		----------------------------------------------------------------------*/
		Servidor.sin_family = AF_INET;
		Servidor.sin_port = htons(2000);
		Servidor.sin_addr.s_addr =  inet_addr("192.168.1.130");
  	 	Longitud_Servidor = sizeof(Servidor);


		/*------------------------------------------------------------------------
			Se genera un n\ufffdmero aleatorio, que es el que se le manda al
			servidor.
		------------------------------------------------------------------------ */
    printf("\nintroduzca la orden: ");
   	scanf("%s", orden);  /* Aleatorio entre 0 y 19 */
   	//printf ("\nEnvio %s\n", orden);


		/*-----------------------------------------------------------------------
			Se env\ufffda mensaje al Servidor
		-----------------------------------------------------------------------*/
		int enviado = sendto (Socket_Cliente, orden, sizeof(orden), 0,
			(struct sockaddr *) &Servidor, Longitud_Servidor);

   	if (enviado < 0)
    	{
			printf("Error al solicitar el servicio\n");
		}
    	else
		{

		/*----------------------------------------------------------------------
			Esperamos la respuesta del Servidor
			----------------------------------------------------------------------- */
			int recibido = recvfrom (Socket_Cliente, (char *)&orden, sizeof(orden), 0,
			(struct sockaddr *) &Servidor, &Longitud_Servidor);

   		if (recibido > 0)
      		printf ("%s\n", orden);
   		else
      		printf ("Error al leer del servidor\n");

		}

		close(Socket_Cliente);
}