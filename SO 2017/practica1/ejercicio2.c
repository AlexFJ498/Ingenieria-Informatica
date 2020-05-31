#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <errno.h>

int main(void){

	pid_t pid;
	pid = fork(); 

	int status,childpid;
    
  	switch(pid){
		case -1:{ 
    
		        perror("fork error");
		        printf("errno value= %d\n", errno); 
        		exit(EXIT_FAILURE);
	    	}
	

    		case 0:{

	 	       printf("Proceso hijo %d; padre = %d\n", getpid(), getppid()); 	
		       exit(EXIT_SUCCESS); 
		}

		default:{ 
       		       sleep(20);
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
	 exit(EXIT_SUCCESS); 
}
