#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

struct datos{
	int repartoN;
	int vector[10];
	int iterator;
	int hilo;
};

void *sumaNumeros(void *aux);

int main(int argc,char* argv[]){
	int i;
	int reparto,resto;
	long suma;
	long sumTotal=0;
	int nHilos=atoi(argv[1]);
	pthread_t th[nHilos];
	struct datos *aux=malloc(sizeof(struct datos));


	//números aleatorios
	srand(time(NULL));
	for(i=0;i<10;i++){
		aux->vector[i]=rand()%10;
	}

	//Repartir sumas
	reparto=10/nHilos;
	resto=10%nHilos;
	aux->iterator=0;	

	//Crear hilos
	printf("Sumando los siguientes números...\n");
	printf("\n");  
	for(i=0;i<10;i++){
		printf("%d,",aux->vector[i]);
	}
	printf("\n");

	for(i=1;i<=nHilos;i++){

		if(i==nHilos){
			aux->repartoN=reparto+resto;
			pthread_create(&th[i-1],NULL,(void *)sumaNumeros,(void *)aux);
			aux->iterator++;
			sleep(1);
		}
		else{
			aux->repartoN=reparto;
			pthread_create(&th[i-1],NULL,(void *)sumaNumeros,(void *)aux);
			aux->iterator++;
			sleep(1);	
		}	
	}

	//Cerrar hilos
	for(i=1;i<=nHilos;i++){
		pthread_join(th[i-1],(void**)&suma);
		sumTotal+=suma;
	}

	//Imprimir resultado
	printf("\n");
	printf("Suma total: %ld\n",sumTotal);
}


void *sumaNumeros(void *aux){
	struct datos * auxiliar= (struct datos*) aux;
	int i;
	long suma=0;
	printf("Hilo %d: suma %d numeros, que son %d, %d y %d
	for(i=auxiliar->iterator;i<auxiliar->repartoN;i++){
		suma+=auxiliar->vector[i];
		printf("%ld\n",suma);
	}

	pthread_exit((void*)suma);
}
