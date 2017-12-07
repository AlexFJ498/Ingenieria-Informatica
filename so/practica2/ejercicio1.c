#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void *hiloMensaje1(char *cad1);
void *hiloMensaje2(char *cad2);

int main(){
	pthread_t thd1,thd2;
	
	char cad1[]="Hola ";
	char cad2[]="mundo";

	pthread_create(&thd1, NULL, (void *) hiloMensaje1,cad1); 
	pthread_join(thd1, NULL); 
    pthread_create(&thd2, NULL, (void *) hiloMensaje2,cad2);
	pthread_join(thd2, NULL);

	pthread_exit(NULL);

	return 0;
}

void *hiloMensaje1(char *cad1){
	int i;
	for(i=0;i<strlen(cad1);i++){
		printf("%c\n",cad1[i]);
		sleep(1);
	}
	pthread_exit(NULL);
}

void *hiloMensaje2(char *cad2){
	int i;
	for(i=0;i<strlen(cad2);i++){
		printf("%c\n",cad2[i]);
		sleep(1);

	}
	pthread_exit(NULL);
}
