

#define CAPACIDAD 5


sem_t huecosvacios;
sem_t huecosllenos;
sem_t mutex;


void productor{

	sem_wait(&huecosvacios);
	sem_wait(&mutex);
		printf("El panadero esta metiendo un pan");
	sem_post(&mutex);
	sempos(&huecosllenos);

}


void consumidor()
{
	sem_wait(&huecosllenos);
	sem_wait(&mutex);
		printf("esta cogiendo pan");
	sem_post(&mutex);
	sem_post(&huecosvacios);
	printf("Consumiendo");
}


int main()
{
	sem_init(&mutex, 0, 1);
	sem_init(&huecosvacios, CAPACIDAD, 0);
	sem_init(&huecosllenos, 0, CAPACIDAD);

	
return 0;
}

	
