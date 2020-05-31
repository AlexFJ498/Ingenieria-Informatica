#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//Tamaño del vector
#define N 10

int v[N];
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;

void *hiloproductor(void *contador);
void *hiloconsumidor(void *contador);

int main(){
	long i;
	long P,C;
	extern int v[N];
	srand(time(NULL));

	//Rellenar el vector de ceros
	for(i=0;i<N;i++){
		v[i]=0;
	}

	//hilos
	printf("Numero de hilos productor: ");
	scanf("%d",&P);
	pthread_t productor[P];
	printf("Numero de hilos consumidores: ");
	scanf("%d",&C);
	pthread_t consumidor[C];

	for(i=0;i<P;i++){
		pthread_create(&productor[i],NULL,(void *)hiloproductor,(void *)i);
	}
	for(i=0;i<C;i++){
		pthread_create(&consumidor[i],NULL,(void *)hiloconsumidor,(void *)i);
	}

	//Cerrar hilos
	for(i=0;i<P;i++){
		pthread_join(productor[i],NULL);
	}
	for(i=0;i<C;i++){
		pthread_join(consumidor[i],NULL);
	}

	//Eliminar semáforo
	pthread_mutex_destroy(&mtx);
}

void *hiloproductor(void *contador){
	int a,i,suma=0;
	int s;
	
	printf("Productor %ld: ",(long) contador);

	//valor aleatorio para la cantidad a incrementar
	a=rand()%1000;

	s=pthread_mutex_lock(&mtx);
		/*Sección crítica*/
		//Añadir elemento
		for(i=0;i<N;i++){
			if(v[i]==0){
				v[i]=a;
				break;
			}
		}

		//Realizar la suma
		for(i=0;i<N;i++){
			suma+=v[i];
		}
		printf("suma= %d\n",suma);
	s=pthread_mutex_unlock(&mtx);

	return NULL;
}

void *hiloconsumidor(void *contador){
	int s,i,suma=0;

	printf("Consumidor %ld: ",(long) contador);
	
	s=pthread_mutex_lock(&mtx);
		/*Sección crítica*/
		//Realizar la suma
		for(i=0;i<N;i++){
			suma+=v[i];
		}
		printf("suma= %d\n",suma);
	s=pthread_mutex_unlock(&mtx);

	return NULL;
}
