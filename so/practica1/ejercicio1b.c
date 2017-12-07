#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <errno.h>

int main(void){
    int n,i;
    pid_t pid;
    int status,childpid;

    printf("Numero de hijos: ");
    scanf("%d",&n);
    for(i=0;i<n;i++){
  	 pid = fork(); 
    
  	 switch(pid){
		case -1:{ 
    
		        perror("fork error");
		        printf("errno value= %d\n", errno); 
        		exit(EXIT_FAILURE);
	    	}
	

    		case 0:{

	 	       printf("Proceso hijo %d; padre = %d\n", getpid(), getppid()); 
		       break;	
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
			exit(EXIT_SUCCESS);
    		}
   	}
    }
}
