#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <errno.h>

void esperar(int seg,char *nombre);

int main(void){
    pid_t pid;

	pid=fork();
	if(pid==0){ //HIJO 1
		esperar(0,"HIJO 1");
	}

	pid=fork();
	if(pid==0){ //HIJO 2
		
		pid=fork();  //NIETO 1
		if(pid==0){ 
			esperar(0,"NIETO 1");
		}

		pid=fork();  //NIETO 2
		if(pid==0){

		   	pid=fork();  //bizNIETO
			if(pid==0){	
			   esperar(0,"BIZNIETO");
			}

			esperar(5,"NIETO 2");	
		}

		esperar(5,"HIJO 2");
	}

	esperar(5,"PADRE");
}



void esperar (int seg, char *nombre){
	int suma,childpid,status;

	sleep(seg);
	suma=getpid()%10;

	while ((childpid=wait(&status))>0){
		if(WIFEXITED(status)>0){
			suma+=WEXITSTATUS(status);
		}
	}

	printf("Soy %s, mi pid es %d, y mi suma es %d\n",nombre,getpid(),suma);

	exit(suma);
}
