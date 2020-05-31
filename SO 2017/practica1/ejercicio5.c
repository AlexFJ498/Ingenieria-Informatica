#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>

int main(int argc, char *argv[]){

	pid_t pid;
	int i,status,childpid;
	
	FILE *f;

	if(argc!=2){
		printf("Comando erroneo: ./ejercicio7.exe <Fichero>\n");
		exit(EXIT_FAILURE);
	}

	else{
		f=fopen(argv[1],"wt");
		
		pid=fork();
		
			switch(pid){
				case -1:{
					perror("fork error\n");
					printf("Errno value=%i\n",errno);
					exit(EXIT_FAILURE);
				}

				case 0:{
					for(i=0;i<5;i++){
						fputs("-----\n",f);
					}
					exit(EXIT_SUCCESS);
				}

				default:{
					for(i=0;i<5;i++){
						fputs("+++++\n",f);
						sleep(1);
						 while ((childpid=wait(&status))>0){
							if (WIFEXITED(status)) {
                				 	   printf("child %d exited, status=%d\n",childpid, WEXITSTATUS(status));
             						}
							 else if (WIFSIGNALED(status)) {
	                				    printf("child %d killed (signal %d)\n", childpid, WTERMSIG(status));
	                				} 
							else if (WIFSTOPPED(status)) {
	                				    printf("child %d stopped (signal %d)\n", childpid, WSTOPSIG(status));
        	        				}		 
	           				}
					
					}
				}
			}
		
	
	fclose(f);
	exit(EXIT_SUCCESS);
	}
}
