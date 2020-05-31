#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <unistd.h>

void *numAleatorios(void* i);
void *invocaHebras(void* sumTotal);

int main(){
	long sumTotal=0;
	pthread_t ptid;


	srand(time(NULL));

	printf("Numero de hebras: ");

	pthread_create(&ptid,NULL,(void *)invocaHebras,(void *)sumTotal);


	pthread_join(ptid,(void**)&sumTotal);
	printf("\n");
	printf("Hebra principal: sumTotal=%ld\n",sumTotal);
}

void *numAleatorios(void* i){
	long n1,n2,suma;

	n1=rand()%20;
	n2=rand()%20;

	suma=n1+n2;

	printf("Hebra %ld: n1=%ld,n2=%ld,suma=%ld\n",(long)i+1,n1,n2,suma);
	pthread_exit((void*)suma);

}

void *invocaHebras(void* sumTotal){
	long n,i;
	long suma;

	scanf("%ld",&n);
	printf("\n");

	pthread_t tid[n];

	for(i=0;i<n;i++){
		pthread_create(&tid[i],NULL,(void*)numAleatorios,(void *)i); 
		sleep(1);
	}
	
	for(i=0;i<n;i++){
		pthread_join(tid[i],(void**)&suma);
		sumTotal+=suma;
	}

	pthread_exit((void*)sumTotal);
}
