#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc,char *argv[]){

	key_t llave;
	pid_t pid;

	int n,i,j,status,childpid;
	int shmid; //id memoria
	int *shmadr=NULL; //puntero memoria a NULL
	int contador=0;

	printf("Numero de hijos: ");
	scanf("%d",&n);


	//Se obtiene clave de memoria
	if((llave=ftok(argv[0],44))==-1){
		printf("Error al crear la clave\n");
		exit(-1);
	}

	
	//Se obtiene id de memoria
	if((shmid=shmget(llave,sizeof(int),IPC_CREAT|0777))==-1){
		printf("Error al crear el segmento de memoria compartida\n");
		exit(-1);
	}


	//Se obtiene puntero a memoria
	if((shmadr=(int *)shmat(shmid,(char *)0,0))==NULL){
		printf("Error al crear conexion a la memoria compartida\n");
		exit(-1);
	}


	for(i=0;i<n;i++){
		pid=fork();

		switch(pid){
			case -1:{
				perror("fork error");
			        printf("errno value= %d\n", errno); 
        			exit(EXIT_FAILURE);
			}

			case 0:{
				while(shmadr[1]!=i){
					usleep(300);
				}
				for(j=0;j<10000;j++){
					shmadr[0]++;
				}
				shmadr[1]++;
				exit(EXIT_SUCCESS);
			}
		
			default:{
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

	while(pid=wait(&status)!=-1);
	contador=shmadr[0];
	printf("Contador= %d\n",contador);
	
	shmdt(shmadr);
	shmctl(shmid,IPC_RMID,0);

	return(EXIT_SUCCESS);
}
