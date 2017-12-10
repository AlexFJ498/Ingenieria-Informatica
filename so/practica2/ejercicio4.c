#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void comprobarFich(char *fichero);
void *contarLineas(char *fichero);

int main(int argc,char **argv){
	//Comprobar que existen los ficheros
	int i;
	for(i=0;i<argc-1;i++){
		comprobarFich(argv[i+1]);
	}

	//Crear 1 hilo por cada fichero
	pthread_t th[argc];
	for(i=0;i<argc-1;i++){
		pthread_create(&th[i],NULL,(void *)contarLineas,argv[i+1]);
		usleep(1000);
	}

	//Sumar las sumas parciales para el resultado final
	long suma;
	long sumTotal=0;
	for(i=0;i<argc-1;i++){
		pthread_join(th[i],(void **)&suma);
		sumTotal+=suma;
	}

	//Imprimir resultado
	printf("\nSuma total de lineas: %ld\n",sumTotal);
}

/*Función que comprueba la existencia de un fichero*/
void comprobarFich(char *fichero){
	FILE *f;
	f=fopen(fichero,"r");
	if(f==NULL){
		printf("Error: el fichero %s no existe\n",fichero);
		exit(-1);
	}
	fclose(f);
}

/*Función de los hilos donde se cuenta las líneas del fichero*/
void *contarLineas(char *fichero){
	FILE *f;
	long contador=0;
	char line[1000];
	int ch;

	f=fopen(fichero,"r");
	while(fscanf(f,"%s",line)!=EOF){
		contador++;
	}	
	fclose(f);

	printf("Fichero '%s': %ld lineas\n",fichero,contador);
	pthread_exit((void*)contador);
}
