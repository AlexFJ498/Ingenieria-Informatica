/*** ejercicio1 ***/
%{
int n=0;
%}
	
entero    [0-9]+
%%
{entero}   {
			if((atoi(yytext) % n) != 0){
				printf("%s",yytext);
				printf("\n");
				fprintf(yyout,yytext);
				
			}
		   }  
.|\n    ;
%%

extern FILE *yyin, *yyout;
int main(int argc,char **argv){
	if(argc!=4){
		printf("numero de argumentos erroneo (./ejercicio1.exe <numero> Entrada.txt Salida.txt\n");
		exit(-1);
	}

	n=atoi(argv[1]);
	yyin=fopen(argv[2],"r");
	yyout=fopen(argv[3],"w");
	yylex();

	return 0;
}
