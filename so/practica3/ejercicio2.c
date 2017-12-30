#include <stdio.h>
#include <string.h>

/*Se utilizarán los datos presentes en el documento de la práctica*/

struct Parametros{
	char nombre[10];
	int t_ejec;
	int t_llegada;
	int t_comienzo;
	int t_finaliza;
	int t_retorno;
	int t_espera;
};

int main(){
	int i,j;
	int ejec_aux;
	struct Parametros proceso[5];

	//Proceso A
	strcpy(proceso[0].nombre,"A");
	proceso[0].t_ejec=8;
	proceso[0].t_llegada=0;

	//Proceso B
	strcpy(proceso[1].nombre,"B");
	proceso[1].t_ejec=4;
	proceso[1].t_llegada=1;
	
	//Proceso C
	strcpy(proceso[2].nombre,"C");
	proceso[2].t_ejec=9;
	proceso[2].t_llegada=2;

	//Proceso D
	strcpy(proceso[3].nombre,"D");
	proceso[3].t_ejec=5;
	proceso[3].t_llegada=3,

	//Proceso E
	strcpy(proceso[4].nombre,"E");
	proceso[4].t_ejec=2;
	proceso[4].t_llegada=4;

	printf("\nProceso|t_ejecucion|t_llegada|t_comienzo|t_finalizacion|t_retorno|t_espera\n");
	printf("----------------------------------------------------------------------------\n");
	for(i=0;i<5;i++){
		if(i==0){
			proceso[i].t_comienzo=0;
		}
		else{
			ejec_aux=proceso[0].t_ejec;
			for(j=1;j<5;j++){
				if(proceso[i].t_ejec>proceso[j].t_ejec){
					ejec_aux+=proceso[j].t_ejec;
				}
			}
			proceso[i].t_comienzo=ejec_aux;
		}

		proceso[i].t_finaliza=proceso[i].t_comienzo+proceso[i].t_ejec;
		proceso[i].t_retorno=proceso[i].t_finaliza-proceso[i].t_llegada;
		proceso[i].t_espera=proceso[i].t_retorno-proceso[i].t_ejec;

		printf("   %s\t     %d\t\t%d\t   %d\t\t%d\t    %d\t      %d\n",proceso[i].nombre,proceso[i].t_ejec,proceso[i].t_llegada,proceso[i].t_comienzo,proceso[i].t_finaliza,proceso[i].t_retorno,proceso[i].t_espera);
	}
}
