#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <errno.h>
#include <wait.h>

int hijo_calculadora(char argv[1]);
int hijo_ficheros(char **argv);

int main(int argc,char *argv[]){
	int i,status;
	
	pid_t pid;


	for(i=0;i<2;i++){ 
		pid=fork();
		switch(pid){

			case -1: {
		        	perror("fork error");
		        	printf("errno value= %d\n", errno); 
		        	exit(-1);
	    		}
			case 0:{
				if(i==0){
					hijo_calculadora(argv[1]);
						
				}
				if(i==1){
					hijo_ficheros(argv);
				}
			}
			exit(EXIT_SUCCESS);
		}
	}
	while(pid=wait(&status)!=-1);
	return(EXIT_SUCCESS);
}

int hijo_calculadora(char *argv){
	if((execlp(argv,argv,NULL))==-1){
		return(EXIT_FAILURE);
	}
	else{
		return(EXIT_SUCCESS);
	}
}

int hijo_ficheros(char *argv[]){
	int i;
	if((execvp(argv[2],&argv[2]))==-1){
		exit(EXIT_FAILURE);
	}
	else{
		exit(EXIT_SUCCESS);
	}

}
