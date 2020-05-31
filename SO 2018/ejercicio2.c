#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

double counter = 0;

#define ITER	1000
#define NHILOS	4

int eligiendo[NHILOS];
int numero[NHILOS];

void *adder(void *);
int max(int v[NHILOS]);

int main(){

    pthread_t hilos[NHILOS];
    int status, i, v[NHILOS];
    extern double counter;
    double *r_value;

	int eligiendo[NHILOS];
	for(int aux=0;aux<NHILOS;aux++){
		eligiendo[aux]=0;
	}

	extern int numero[NHILOS];
	for(int aux=0;aux<NHILOS;aux++){
		numero[aux]=0;
	}

    // Create NHILOS threads
    for (i = 0; i < NHILOS; i++) {
	v[i] = i;
	if ((status = pthread_create(&hilos[i], NULL, adder, (void *) &v[i])))
	    exit(status);
    }

    // Wait threads
    for (i = 0; i < NHILOS; i++) {
	pthread_join(hilos[i], (void **) &r_value);
	printf("Value returned by %lu thread: %lf\n", hilos[i], *r_value);
    }

    // Final result
    fprintf(stdout, "%f\n", counter);

    return 0;
}

void *adder(void *p){
	extern int eligiendo[NHILOS];
	extern int numero[NHILOS];
	int j;

    double l, *to_return;
    extern double counter;
    int *id, i;

    id = (int *) p;

	while(1){
		eligiendo[*id]=1;
		numero[*id]=1+max(&numero[NHILOS]);
		eligiendo[*id]=0;

		for(j=0;j<NHILOS;j++){
			while(eligiendo[j]);
			while((numero[j]!=0) && (numero[j]<numero[*id] || (numero[j]==numero[*id] && j<*id)));
		}

		//--------------------
		//SECCIÓN CRÍTICA
		//--------------------

		for(i=0;i<ITER;i++){
			l=counter;
			fprintf(stdout,"Hilo %d: %f\n",*id,counter);
			l++;
			counter=l;
    	}

		numero[*id]=0;

    	to_return=malloc(sizeof(double));
	
    	*to_return=counter;

 		pthread_exit((void *) to_return);
	}
}

int max(int v[]){
	int max=-9999;
	int i;

	for(i=0;i<sizeof(*v);i++){
		if(v[i]>max){
			max=v[i];
		}
	}

	return max;
}
