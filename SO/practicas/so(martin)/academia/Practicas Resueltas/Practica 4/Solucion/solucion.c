#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>

// Solucion al problema del productor consumidor con variables
// condicion.

#define N		10
#define ITER		1000
#define CONS		3
#define PRODS		2
#define FIN 		-1

int contador, bufer[N], p_index, c_index;

pthread_cond_t full, empty;// Tipo de dato para declarar la variable. Valen mas de 0 o 1.
pthread_mutex_t mutex;// Es la seccion critica


int main()
{
    extern int contador, p_index, bufer[N], c_index;
    pthread_t prod[PRODS], cons[CONS];
    int v[PRODS + CONS], i, status, *p_suma, *c_suma, p_total =
	0, c_total = 0;
    void *Productor(void *), *Consumidor(void *);
    pthread_attr_t atributos;
    extern pthread_cond_t full, empty;
    extern pthread_mutex_t mutex;

    // Fija la concurrencia inicial.
    // thr_setconcurrency (PRODS+CONS+1);
    pthread_attr_init(&atributos);
    contador = p_index = c_index = 0;
    srand(-time(NULL));

    // Inicializa las variables condicion
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < PRODS; i++) {
	v[i] = i;
	if ((status =
	     pthread_create(&prod[i], &atributos, Productor, &v[i])))
	    exit(status);
    }

    for (i = 0; i < CONS; i++) {
	v[i + PRODS] = i;
	if ((status = pthread_create(&cons[i], &atributos, Consumidor,
				     &v[i + PRODS])))
	    exit(status);
    }

    // Espera a que finalicen.
    for (i = 0; i < PRODS; i++) {
	pthread_join(prod[i], (void **) &p_suma);
	p_total += *p_suma;
	printf("Total productor %d: %d\n", i, *p_suma);
    }

    // Indica el fin a los consumidores.
    for (i = 0; i < CONS; i++) {
	// Acceso a contador y bloqueo si no se puede producir.
	pthread_mutex_lock(&mutex);
	while (contador == N)
	    pthread_cond_wait(&full, &mutex);

	// Acceso al b?fer.
	bufer[p_index] = FIN;
	p_index = (p_index + 1) % N;

	// Despierta a los posibles consumidores.
	if (++contador == 1)
	    pthread_cond_broadcast(&empty);

	pthread_mutex_unlock(&mutex);

    }

    fprintf(stdout, "Marcado final de bufer.\n");

    // Espera a que finalicen.
    for (i = 0; i < CONS; i++) {
	pthread_join(cons[i], (void **) &c_suma);
	c_total += *c_suma;
	printf("Total consumidor %d: %d\n", i, *c_suma);
    }

    fprintf(stdout, "Suma de productores: %d\n", p_total);
    fprintf(stdout, "Suma de consumidores: %d\n", c_total);

    return 0;
}


void *Productor(void *p)
{
    int i, producido, *suma, *id;
    extern int p_index, contador, bufer[N];
    extern pthread_cond_t full, empty;
    extern pthread_mutex_t mutex;

    suma = malloc(sizeof(int));
    *suma = 0;
    id = (int *) p;

    for (i = 0; i < ITER; i++) {
	*suma += (producido = rand() % 100);

	// Acceso a contador y bloqueo si no se puede producir.
	pthread_mutex_lock(&mutex);//Va a entrar enm la seccion critica y la bloquea.
	while (contador == N)
	    pthread_cond_wait(&full, &mutex);//Como ya he llegado al total, bloqueo el full.

	// Acceso al b?fer.
	bufer[p_index] = producido;
	p_index = (p_index + 1) % N;

	// Despierta a los posibles consumidores.
	if (++contador == 1) {
	    pthread_cond_broadcast(&empty);//Para despertar a alguien.
	    fprintf(stdout, "Productor %d: Signal en empty\n", *id);
	}

	pthread_mutex_unlock(&mutex);

	fprintf(stdout, "Productor %d: %d, contador: %d\n", *id,
		producido, contador);
    }

    // Despierta a un posible productor en espera.
    pthread_mutex_lock(&mutex);
    if (contador != N)
	pthread_cond_signal(&full);
    pthread_mutex_unlock(&mutex);

    pthread_exit((void *) suma);

}

void *Consumidor(void *p)
{
    int consumido = 0, *suma, *id;
    extern int contador, c_index, bufer[N];
    extern pthread_cond_t full, empty;
    extern pthread_mutex_t mutex;

    suma = malloc(sizeof(int));
    *suma = 0;
    id = (int *) p;

    while (consumido != -1) {
	// Acceso a contador y bloqueo si no se puede consumir.
	pthread_mutex_lock(&mutex);
	while (contador == 0)
	    pthread_cond_wait(&empty, &mutex);


	// Acceso al b?fer.
	*suma += (consumido = bufer[c_index]);
	c_index = (c_index + 1) % N;

	// Despierta a los posibles productores.
	if (--contador == N - 1) {
	    pthread_cond_broadcast(&full);
	    fprintf(stdout, "Consumidor %d: Signal en full\n", *id);
	}

	pthread_mutex_unlock(&mutex);

	fprintf(stdout, "Consumidor %d: %d, contador: %d\n", *id,
		consumido, contador);
    }

    (*suma)++;
    fprintf(stdout, "Fin de consumidor %d\n", *id);

    // Despierta a los posibles consumidores en espera.
    pthread_mutex_lock(&mutex);
    if (contador != 0)
	pthread_cond_broadcast(&empty);
    pthread_mutex_unlock(&mutex);


    pthread_exit((void *) suma);
}
