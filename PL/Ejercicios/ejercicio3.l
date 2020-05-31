/*** ejercicio3 ***/

/*** Zona de las declaraciones o definiciones ***/
%{
char *fichero;
   /* Descripción
	El analizador léxico distingue entre verbos, adjetivos, 
	adverbios, artículos,... 
 */
%}

letra  [a-zA-Z]
digito [0-9]
subrayado "_"
identificador {letra}({letra}|{digito}|{subrayado}({letra}|digito}))*
numero {digito}+
cadena "'"([^']|"\\\'")*"'"

%x ESTADO_COMENTARIO
%%
"*y*"	      	{
			  		BEGIN ESTADO_COMENTARIO; 
			  	}

<ESTADO_COMENTARIO>"#"/(.|\n)  {
			          printf("\n No se pueden anidar comentarios\n"); 
				  return 0;
				 }

<ESTADO_COMENTARIO>"*y*"          { 
				  BEGIN 0; 
				  }      

<ESTADO_COMENTARIO>.        {;}

"#"				{
					BEGIN ESTADO_COMENTARIO;
				}

<ESTADO_COMENTARIO>"\n" {BEGIN 0;}

[\t ]+		/* ignora los espacios en blanco */ ;

inicio |
fin |
leer |
escribir |
si |
entonces |
si_no |
fin_si |
mientras |
hacer |
fin_mientras |
repetir |
hasta_que |
para |
desde |
hasta |
paso |

fin_para		{ printf("%s: es una palabra reservada\n", yytext); }

{identificador}   { printf("%s: es un identificador\n", yytext); }

{numero}   { printf("%d: es un numero\n", atoi(yytext)); }

{cadena}   { printf("%s: es una cadena\n", yytext); }

":="      { printf("%s: es un operador de asignacion\n", yytext); }
"+"       { printf("%s: es un operador aritmetico (suma)\n", yytext); }
"-"       { printf("%s: es un operador aritmetico (resta)\n", yytext); }
"*"       { printf("%s: es un operador aritmetico (producto)\n", yytext); }
"/"       { printf("%s: es un operador aritmetico (division)\n", yytext); }
"__mod"   { printf("%s: es un operador aritmetico (modulo)\n", yytext); }
"**"      { printf("%s: es un operador aritmetico (potencia)\n", yytext); }

"||"      { printf("%s: es un operador alfanumerico (concatenacion)\n", yytext); }

"<"       { printf("%s: es un operador relacional (menor que)\n", yytext); }
"<="      { printf("%s: es un operador relacional (menor o igual que)\n", yytext); }
">"       { printf("%s: es un operador relacional (mayor que)\n", yytext); }
">="      { printf("%s: es un operador relacional (mayor o igual que)\n", yytext); }
"=="      { printf("%s: es un operador relacional (igual)\n", yytext); }
"<>"      { printf("%s: es un operador relacional (distinto)\n", yytext); }

".o."     { printf("%s: es un operador logico (disyuncion logica)\n", yytext); }
".y."     { printf("%s: es un operador logico (conjuncion logica)\n", yytext); }
".no."    { printf("%s: es un operador logico (negacion logica)\n", yytext); }

";"       { printf("%s: fin de sentencia\n", yytext); }
"("       { printf("%s: parentesis izquierdo\n", yytext); }
")"       { printf("%s: parentesis derecho\n", yytext); }

.		 	{
	 printf("%s:  No reconocido; puede ser un nombre \n", yytext); }



%%

/****Zona de funciones auxiliares ***/

extern FILE *yyin, *yyout;
int main(int argc, char **argv){
	if(argc!=2){
		printf("Numero de argumentos erroneo (./ejercicio3.exe <fichero>\n");
		exit(-1);
	}

	fichero=argv[1];
	yyin=fopen(fichero,"r");
	yylex();

	return 0;
}
