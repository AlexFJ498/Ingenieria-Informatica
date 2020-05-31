#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct elem{
	long m[3][3];
	long v[3];
	long iterator;
};

void *hiloPadre(void *Operaciones);
void *hiloHijo(void *Operaciones);

int main(){
	int i,j;
	pthread_t padre;
	struct elem *Operaciones;
	Operaciones->iterator=0;

	//Rellenar matriz
	printf("Rellenar matriz:\n");
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			printf("m[%d][%d]: ",i,j);
			scanf("%ld",&Operaciones->m[i][j]);
		}
	}
	printf("\n");

	//Rellenar vector
	printf("Rellenar vector:\n");
	for(i=0;i<3;i++){
		printf("v[%d]: ",i);
		scanf("%ld",&Operaciones->v[i]);
	}
	printf("\n");

	//Visualizar matriz
	printf("\nLa matriz es:\n");
	for(i=0;i<3;i++){
		printf("(");
		for(j=0;j<3;j++){
			printf(" %ld",Operaciones->m[i][j]);
		}
		printf(" )\n");
	}

	//Visualizar vector
	printf("\nEl vector es:\n");
	printf("(");
	for(i=0;i<3;i++){
		printf(" %ld",Operaciones->v[i]);
	}
	printf(" )\n");

	//Llamar al padre

	pthread_create(&padre,NULL,(void *)hiloPadre,(void *)Operaciones);

	pthread_join(padre,(void **)&Operaciones);

	//Imprimir resultado
	printf("\nVector final:\n(");
	for(i=0;i<3;i++){
		printf(" %ld",Operaciones->v[i]);
	}
	printf(" )\n");
}

void *hiloPadre(void * Operaciones){
	int i;
	long fila;
	pthread_t th[3];
	struct elem *aux=(struct elem *) Operaciones;

	//Llamar a un hilo para una fila
	printf("\n\nMultiplicando...\n");
	for(i=0;i<3;i++){
		pthread_create(&th[i],NULL,(void *) hiloHijo,(void *)Operaciones);
		usleep(1000);
	}

	//Cerrar hilos
	for(i=0;i<3;i++){
		pthread_join(th[i],(void **)&fila);
		aux->v[i]=fila;
	}

	pthread_exit((void *)aux);
}

void *hiloHijo(void * Operaciones){
	struct elem *aux=(struct elem *) Operaciones;
	long fila;

	fila=aux->m[aux->iterator][0]*aux->v[0]+aux->m[aux->iterator][1]*aux->v[1]+aux->m[aux->iterator][2]*aux->v[2];
	aux->iterator++;

	pthread_exit((void *)fila);
}
