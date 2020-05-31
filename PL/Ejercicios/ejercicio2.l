/*** ejercicio1 ***/
%{
#include <stdio.h>
#include <string.h>

char *antigua;
char *nueva;
int contador=0;
%}
espacio		[ \t\n]
espacios	{espacio}+
palabra   [a-zA-Z]*
%%
{espacios} { ; }
{palabra}   {
			 if(strcmp(yytext,antigua)==0){
				fprintf(yyout,"%s ",nueva);
				contador++;
			 }
			 else{
				fprintf(yyout,"%s ",yytext);
 			 }
		    }  

%%

extern FILE *yyin, *yyout;
int main(int argc,char **argv){
	if(argc!=4){
		printf("numero de argumentos erroneo (./ejercicio2.exe fichero.txt antigua nueva\n");
		exit(-1);
	}
	FILE *f,*aux;
	char ch;

	f=fopen(argv[1],"r");
	aux=fopen("auxiliar.txt","w");

	while ((ch = fgetc(f)) != EOF)
    	fputc(ch, aux);
	fclose(f);
	fclose(aux);

	antigua=argv[2];
	nueva=argv[3];

	yyin=fopen("auxiliar.txt","r");
	yyout=fopen(argv[1],"w");
	yylex();
	printf("Numero de palabras sustituidas: %d\n",contador);
	remove("auxiliar.txt");

	return 0;
}
