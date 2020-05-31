/*** ejercicio4 ***/
%{
#include <stdio.h>
#include <string.h>
int opcion;
int contador=0;
char *userAux;
char *user;
char *date;
%}
espacio		[ \t\n]
espacios	{espacio}+
digito      [0-9]
numero      {digito}+
usuario     ^[a-zA-Z]+
documento   [a-zA-Z]+
fecha       {numero}"/"{numero}"/"{numero}
hora        {numero}":"{numero}
%%
{espacios} { ; }

{usuario}   {
	         if(opcion==0){
				if(strcmp(user,yytext)==0){
					contador++;
				}
			 }
					
			 if(opcion==1){
				if(strcmp(user,yytext)==0){
					userAux=user;
				}else{	
					userAux=yytext;
				}
			 }
		  } 

{fecha}   {
			if(opcion==1){
				if(strcmp(user,userAux)==0 && strcmp(date,yytext)==0){
					contador++;
				}
			}
		  }

{documento} { ; }
{hora} { ; }
%%

extern FILE *yyin, *yyout;
int main(int argc,char **argv){
	if(argc==3){
		opcion=0;
		yyin=fopen(argv[1],"r");
		user=argv[2];
	} else if(argc==4){
		opcion=1;
		yyin=fopen(argv[1],"r");
		user=argv[2];
		date=argv[3];
	}
	else{
		printf("Numero de argumentos erroneo (./ejercicio4.exe impresora.txt <usuario> <fecha>\n");
		exit(-1);
	}

	yylex();

	if(opcion==0){
		printf("\nNumero de documentos impresos por %s: %d\n",user,contador);
	} else{
		printf("Numero de documentos impresos por %s en %s: %d\n",user,date,contador);
	}

	return 0;
}
