#include <stdlib.h> 
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

struct datos{
	int repartoN;
	int vector[10];
	int iterator;
	int hilo;
};

void *sumaNumeros(void *aux);

int main(int argc,char* argv[]){
	//Comprobar argumentos
	if(argc!=2){
		printf("Error al ejecutar el programa: 'ejercicio3.exe <numero de hilos>\n");
		exit(-1);
	}

	//Comprobar número de hilos
	if(atoi(argv[1])<=0 || atoi(argv[1])>10){
		printf("Error: el numero de hilos debe estar comprendido entre 1 y 10\n");
		exit(-1);
	}

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
	aux->hilo=1;

	//Crear hilos
	printf("Sumando los siguientes números...\n");
	for(i=0;i<10;i++){
		printf("%d ",aux->vector[i]);
	}
	printf("\n");

	for(i=1;i<=nHilos;i++){
		if(i==nHilos){
			aux->repartoN=reparto+resto;
			pthread_create(&th[i-1],NULL,(void *)sumaNumeros,(void *)aux);
		}
		else{
			aux->repartoN=reparto;
			pthread_create(&th[i-1],NULL,(void *)sumaNumeros,(void *)aux);
			usleep(1000);	
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

	printf("\nHilo %d: sumando",auxiliar->hilo);
	for(i=0;i<auxiliar->repartoN;i++){
		printf(" %d",auxiliar->vector[auxiliar->iterator]);
		suma+=auxiliar->vector[auxiliar->iterator];
		auxiliar->iterator++;
	}
	printf("...\nSuma=%ld\n",suma);
	auxiliar->hilo++;
	pthread_exit((void*)suma);
}
