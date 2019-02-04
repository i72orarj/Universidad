#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


struct reparto{

	int *v;
	int desde;
	int hasta;
};


void * suma(void * parametro){

	struct reparto *r;

	//r = (struct reparto *)malloc(sizeof(struct reparto));


	r = (struct reparto *)parametro;

	int *suma;
	int i;


	suma = (int *)malloc(sizeof(int));
	*suma=0;

	for(i=r->desde ; i<r->hasta ; i++){
		printf("%d ",r->v[i]);

		*suma=*suma+r->v[i];
	}

pthread_exit((void*) suma);
}




int main(){


	pthread_t hebras[2];
	struct reparto repartir[2];
	int v[10];
	int i,s=0;
	int *puntero;


	for(i=0 ; i<10 ; i++){

		v[i]=i+3;
		s=s+v[i];
	}
	
	printf("La suma sin hilos es %d\n",s);	

	repartir[0].v=v;
	repartir[0].desde=0;
	repartir[0].hasta=5;

	repartir[1].v=v;
	repartir[1].desde=5;
	repartir[1].hasta=10;
	


	for(i=0 ; i<2 ; i++){

		pthread_create(&hebras[i], NULL, (void *) suma, (void *) &repartir[i]);

	}


	s=0;
	for(i=0 ; i<2 ; i++){

		pthread_join(hebras[i], (void **) &puntero);
		s=s+*puntero; //tenemos que ir guardado la suma por que sino cada vez que llama a la funcion vuelve a 0
		printf("La suma sin hilos es %d\n",s);

	}

	
	printf("La suma sin hilos es %d\n",s);


return 0;
}
