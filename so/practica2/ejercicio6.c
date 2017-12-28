#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

void *incrementaCont(void * contador);

int main(){
	long contador,aux,resultado;
	int n,i;

	//Número de hilos
	printf("Número de hilos: ");
	scanf("%d",&n);
	if(n<=0){
		printf("Error: introduzca un numero valido de hilos\n");
		exit(-1);
	}
	pthread_t th[n];

	//Crear hilos
	contador=0;
	resultado=0;
	for(i=0;i<n;i++){
		pthread_create(&th[i],NULL,(void *) incrementaCont,(void *)contador);
	}	
	
	//Cerrar hilos
	for(i=0;i<n;i++){
		pthread_join(th[i],(void **)&aux);
		resultado+=aux;
	}

	//Imprimir resultado
	printf("Valor final del contador: %ld\n",resultado);
}

void *incrementaCont(void * contador){
	long aux= (long) contador;
	aux+=100;

	pthread_exit((void *)aux);
}
