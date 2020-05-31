/*** ejercicio5 ***/
%{
#include <stdio.h>
#include <string.h>
char *mensaje;
char *clave;
int contadorClave=-1;
char letraCadena[30];
char resultado[200];
char abecedario[30]={"abcdefghijklmnopqrstuvwxyz"};
int contador;
int i;
%}
letra     [a-zA-Z]
espacio	  [ ]

%%
{letra}   {
			contadorClave++;
			if(contadorClave>sizeof(clave)){
				contadorClave=1;
			}
			
			contador=-1;
	
			for(i=0;i<26;i++){
				contador++;
				if(abecedario[i]==clave[contadorClave]){
				break;
				}
			}
				
			*letraCadena=abecedario[(numeroCifrado(yytext)+contador)%26];

			strcat(resultado,letraCadena);
		  }

{espacio} { strcat(resultado," "); }

%%
int numeroCifrado(char *letra);

extern FILE *yyin, *yyout;
int main(int argc,char **argv){
	if(argc!=3){
		printf("Numero de argumentos erroneo (./ejercicio5.exe <mensaje> <clave>\n");
		exit(-1);
	}
	mensaje=argv[1];
	clave=argv[2];

	FILE *f;

	f=fopen("Auxiliar.txt","w");
	fprintf(f,mensaje);
	fclose(f);

	yyin=fopen("Auxiliar.txt","r");
	yylex();

	printf(" Mensaje: %s\n Clave: %s\n Criptograma: %s\n",mensaje,clave,resultado);
	remove("Auxiliar.txt");

	return 0;
}

int numeroCifrado(char *letra){
	int contador=-1;
	int i;

	for(i=0;i<26;i++){
		contador++;
		if(abecedario[i]==letra[0]){

			return contador;
		}
	}
	printf("Letra no encontrada\n");
	return -1;
}
