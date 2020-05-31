/*EL PROBLEMA DEL PRODUCTOR-CONSUMIDOR ELEGIDO ES EL MISMO QUE EL DEL EJERCICIO 7, POR LO QUE SE TRATA DEL MISMO PROBLEMA CON LA IMPLEMENTACIÓN DE LÍMITES EN EL BUFFER*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N_PROVEEDORES 5  //NÚMERO DE PROVEEDORES/MODELOS DE CAMISETA DEL EJERCICIO
#define LIMITE_BUFFER 600  //LÍMITE DE CAMISETAS PARA CADA MODELO
#define CANTIDAD_INICIAL 500  //CANTIDAD INICIAL DE CAMISETAS PARA CADA MODELO (DEBE SER MENOR QUE LIMITE_BUFFER)
int camisetas[N_PROVEEDORES];
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;

void *simulaCompra(void *contador);
void *simulaSuministro(void *contador);

int main(){
	int n;
	long i;
	srand(time(NULL));

	//Generar n clientes
	printf("Número de clientes: ");
	scanf("%d",&n);
	pthread_t cliente[n];

	//Generar proveedores
	pthread_t proveedores[N_PROVEEDORES];
	
	//crear el stock de cada modelo (cantidad inicial de camisetas: 500)
	printf("Valores iniciales:\n");
	for(i=0;i<N_PROVEEDORES;i++){
		camisetas[i]=CANTIDAD_INICIAL;
		printf("camisetas[%ld]=%d\n",i,CANTIDAD_INICIAL);
	}
	printf("\nClientes: %d\n",n);
	printf("Proveedores: %d\n\n",N_PROVEEDORES);
	
	//hilos Clientes
	for(i=0;i<n;i++){ 

		pthread_create(&cliente[i],NULL,(void *)simulaCompra,(void *)i);
	}

	//hilos Suministros
	for(i=0;i<N_PROVEEDORES;i++){

		pthread_create(&proveedores[i],NULL,(void *)simulaSuministro,(void *)i);
	}

	//Cerrar hilos
	for(i=0;i<n;i++){
		pthread_join(cliente[i],NULL);
	}
	for(i=0;i<N_PROVEEDORES;i++){
		pthread_join(proveedores[i],NULL);
	}

	//Imprimir el número de camisetas finales
	printf("\nResultado final:\n");
	for(i=0;i<N_PROVEEDORES;i++){
		printf("camisetas[%ld]=%d\n",i,camisetas[i]);
	}
	pthread_mutex_destroy(&mtx);
}

void *simulaCompra(void *contador){
	int m,c,i;
	int s;

	printf("Cliente %ld: ",(long)contador);

	//valor aleatorio para el modelo de camiseta
	m=rand()%N_PROVEEDORES;
	
	//valor aleatorio para la cantidad a comprar (máximo 100)
	c=rand()%100;
	
	s=pthread_mutex_lock(&mtx);
		/*Sección crítica*/
			printf("camisetas[%d]=%d-%d",m,camisetas[m],c);
			if((camisetas[m]-=c)<0){								//BUFFER VACÍO
				printf("<0. Buffer vacio, no se realiza compra\n");
				camisetas[m]+=c;
				s=pthread_mutex_unlock(&mtx);
				return NULL;
			}
			printf("=%d\n",camisetas[m]);
		s=pthread_mutex_unlock(&mtx);
	return NULL;
}

void *simulaSuministro(void *contador){
	int m,c,i;
	int s;
	
	printf("Proveedor %ld: ",(long)contador);

	//valor aleatorio para el modelo de camiseta
	m=rand()%N_PROVEEDORES;

	//valor aleatorio para la cantidad a incrementar
	c=rand()%100;

	s=pthread_mutex_lock(&mtx);
		/*Sección crítica*/
			printf("camisetas[%d]=%d+%d",m,camisetas[m],c);
			if((camisetas[m]+=c)>LIMITE_BUFFER){					//BUFFER LLENO
				printf(">%d. Buffer lleno, no se realiza suministro\n",LIMITE_BUFFER);
				camisetas[m]-=c;
				s=pthread_mutex_unlock(&mtx);
				return NULL;
			}
			printf("=%d\n",camisetas[m]);
		s=pthread_mutex_unlock(&mtx);
	return NULL;
}
